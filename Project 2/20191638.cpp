#include <stdio.h>
#include <cstring>
#include "mysql.h"

#pragma warning(disable:4996)
#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "162534Qwe!";
const char* db = "project2";

using namespace std;

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		char buffer[1000];
		FILE* fp = fopen("20191638.txt", "rt");
		if (fp == NULL)
		{
			printf("file does not exist!\n");
			return 0;
		}

		while (fgets(buffer, 1000, fp)) {
			mysql_query(connection, buffer);
		}

		bool main_flag = false; // quit flag
		int state = 0;
		while (!main_flag)
		{
			int type_num;

			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t0. QUIT\n");
			printf("type number of query (Please enter only one number) : ");
			scanf("%d", &type_num);
			if (type_num == 1)
			{
				int subtype_num;
				bool subflag = false; // type 1 quit flag
				while (!subflag)
				{
					printf("\n----- Subtypes int TYPE I -----\n");
					printf("\t1. TYPE I-1.\n");
					printf("\t2. TYPE I-2.\n");
					printf("\t3. TYPE I-3.\n");
					printf("type number of query (Please enter only one number) : ");
					scanf("%d", &subtype_num);

					if (subtype_num == 1)
					{
						printf("---- TYPE I-1 ----\n\n");
						printf("** Find all customers who had a package on the truck at the time of the crash.**\n");
						while (1)
						{
							char truck_num[10];
							printf("Which truck? (please input between 1~30) : ");
							scanf("%s", truck_num);
							if (!strcmp(truck_num, "0"))	break;
							printf("\n\n Customers name : ");
							char q1[200] = "create table temp as select b.sender_id from Bill b join Shipping s on b.package_id = s.package_id join Transport t on s.transport_id = t.transport_id where t.transport_id =  ";
							strcat(q1, truck_num);
							mysql_query(connection, q1);
							char q2[200] = "select c.name from Customer c join temp on c.customer_id = temp.sender_id ";
							char q3[100] = "drop table temp";
							
							int result = mysql_query(connection, q2);
							if (result == 0)
							{
								sql_result = mysql_store_result(connection);
								while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
								{
									printf("%s  ", sql_row[0]);
								}
								mysql_free_result(sql_result);
							}
							mysql_query(connection, q3);
							printf("\n\n");
						}
					}
					else if (subtype_num == 2)
					{
						printf("\n---- TYPE I-2 ----\n");
						printf("** Find all recipients who had a package on that truck at the time of the crash.**\n");
						while (1)
						{
							char truck_num[10];
							printf("Which truck? (please input between 1~30) : ");
							scanf("%s", truck_num);
							if (!strcmp(truck_num, "0"))	break;
							printf("\n\nRecipient Name : ");
							char q1[200] = "create table temp select distinct b.receiver_id from Bill b join Shipping s on b.package_id = s.package_id join Transport t on s.transport_id = t.transport_id where t.transport_id=  ";
							strcat(q1, truck_num);
							mysql_query(connection, q1);
							char q2[200] = "select c.name from Customer c join temp on c.customer_id = temp.receiver_id";
							char q3[100] = "drop table temp";
							int result = mysql_query(connection, q2);
							if (result == 0)
							{
								sql_result = mysql_store_result(connection);
								while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
								{
									printf("%s ", sql_row[0]);
								}
								mysql_free_result(sql_result);
								printf("\n\n");
							}
							mysql_query(connection, q3);
						}
					}
					
					else if (subtype_num == 3)
					{
						printf("\n---- TYPE I-3 ----\n");
						printf("** Find the last successful delivery by that truck prior to the crash.**\n");
						while (1)
						{
							char truck_num[10];
							printf("Which truck? (please input between 1~30) : ");
							scanf("%s", truck_num);
							if (!strcmp(truck_num, "0"))	break;
							printf("\n\nSuccessful Delivery : ");
							char q1[250] = "CREATE TABLE crushed_package AS SELECT p.package_id, p.departure_time, p.arrival_time FROM Package p JOIN Shipping s ON p.package_id = s.package_id JOIN Transport t ON s.transport_id = t.transport_id WHERE t.transport_id = ";
							char q2[200] = "SELECT c.package_id, c.departure_time, c.arrival_time FROM crushed_package c WHERE c.arrival_time IS NOT NULL ORDER BY c.arrival_time DESC LIMIT 1";
							char q3[100] = "drop table crushed_package";
							strcat(q1, truck_num);
							mysql_query(connection, q1);
							state = mysql_query(connection, q2);
							if (state == 0)
							{
								sql_result = mysql_store_result(connection);
								while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
								{
									printf("\n package id : %s		departure time : %s		arrival time : %s\n", sql_row[0], sql_row[1], sql_row[2]);
								}
								mysql_free_result(sql_result);
							}
							mysql_query(connection, q3);
							printf("\n\n");
						}
					}
					else if (subtype_num == 0)
					{
						subflag = true;
						printf("\n");
					}
					else
					{
						printf("Didn't i ask you to enter only one number???? \n");
						continue;
					}
				}
			}
			else if (type_num == 2)
			{
				printf("\n---- TYPE II ----\n");
				while (1) {
					char year[10];
					printf("** Find the customer who has shipped the most packages in certain year**\n");
					printf(" Which Year? (2022 or 2023) : ");
					scanf("%s", year);
					if (!strcmp(year,"0")) break;
					printf("\n\nCustomer Name and number of packages : ");
					char q1[1000] = "create table temp as select sender_id , count(*) cnt from Bill where Year(sign_date) = ";
					char q2[200] = " group by sender_id ORDER BY cnt DESC LIMIT 1";
					char q3[200] = "select c.name , temp.cnt from Customer c join temp on temp.sender_id = c.customer_id";
					char q4[100] = "drop table temp;";
					strcat(q1, year);
					strcat(q1, q2);
					mysql_query(connection, q1);
					state = mysql_query(connection, q3);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("	%s %s", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					mysql_query(connection, q4);
					printf("\n\n");
				}
			}
			else if (type_num == 3)
			{
				printf("\n--- TYPE III ----\n");
				while (1) {
					char year[10];
					printf("** Find the customer who has spent the most money on shipping in the certain year **\n");
					printf(" Which Year? (2022 or 2023) : ");
					scanf("%s", year);
					if (!strcmp(year,"0")) break;
					printf("\n\nCustomer Name and total payment amount : ");
					char q1[1000] = "create table temp as select sender_id, sum(cost) pay from Bill where year(sign_date) =";
					char q2[100] = " group by sender_id";
					char q3[200] = "SELECT c.name , t.pay FROM Customer c JOIN temp t ON c.customer_id = t.sender_id WHERE t.pay = (SELECT MAX(pay) FROM temp)";
					char q4[100] = "drop table temp;";
					strcat(q1, year);
					strcat(q1, q2);
					mysql_query(connection, q1);
					state = mysql_query(connection, q3);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%s %s", sql_row[0],sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					mysql_query(connection, q4);
					printf("\n\n");
				}
			}
			else if (type_num == 4)
			{
				printf("\n--- TYPE IV ----\n");
				printf("** Find those packages that were not delivered within the promised time.**\n");
				char q1[200] = "create table t1 as select package_id from Package where arrival_time IS NULL";
				char q2[200] = "create table t2 as select package_id from Package where timeliness = 'overnight' and departure_time + INTERVAL 1 DAY  < arrival_time";
				char q3[200] = "create table t3 as select package_id from Package where timeliness = 'second_day' and departure_time + INTERVAL 2 DAY  < arrival_time";
				char q4[200] = "create table t4 as select package_id from Package where timeliness = 'longer' and departure_time + INTERVAL 5 DAY  < arrival_time";
				char q5[300] = "SELECT package_id FROM t1 UNION SELECT package_id FROM t2 UNION SELECT package_id FROM t3 UNION SELECT package_id FROM t4 ORDER BY package_id ASC";
				char q6[100] = "drop table t1,t2,t3,t4";
				mysql_query(connection, q1);
				mysql_query(connection, q2);
				mysql_query(connection, q3);
				mysql_query(connection, q4);
				state = mysql_query(connection, q5);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s ", sql_row[0]);
					}
					mysql_free_result(sql_result);
					printf("\n\n");
				}
				mysql_query(connection, q6);
			}
			else if (type_num == 5)
			{
				while (1) {

					char input[10];
					char month[10];
					char year[10];

					printf("** Generate the bill for each customer for the certain month.**\n");
					printf("** please input 2022-06 ~ 2023-06 **\n");
					printf(" Which Month(YYYY-MM)? : ");
					scanf("%s", input);
					sscanf(input, "%[^-]-%[^-]", year, month);

					if (!strcmp(year, "0") || !strcmp(month, "0")) break;

					char names[100][100];
					char amount[100][100];
					char method[100][100];
					int index = 0;

					char q1[200] = "select c.name , a.amount, c.payment_method from Customer c join amount_owed a on c.customer_id = a.user_id";
					state = mysql_query(connection, q1);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							strcpy(names[index], sql_row[0]);
							strcpy(amount[index], sql_row[1]);
							strcpy(method[index], sql_row[2]);
							index++;
						}
						mysql_free_result(sql_result);
					}

					for (int i = 0; i < index; i++) {
						printf("| %-15s | %-15s | %-15s |\n", "customer name", "amount owed", "payment method");
						printf("| %-15s | %-15s | %-15s |\n\n",names[i],amount[i],method[i]);
						printf("| %-20s | %-10s | %-15s | %-15s | %-30s |\n\n", "Package Number", "Cost", "Order Type", "Payment Method", "Order Date");

						char q2[300] = "select b.package_id , b.cost , b.order_type, c.payment_method, b.sign_date from Bill b join Customer c on b.sender_id = c.customer_id where c.name = ";
						strcat(q2, "\"");
						strcat(q2, names[i]);
						strcat(q2, "\"");
						strcat(q2, " and month(b.sign_date) = ");
						strcat(q2, month);
						strcat(q2," and year(b.sign_date) = ");
						strcat(q2, year);

						state = mysql_query(connection, q2);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("| %-20s | %-10s | %-15s | %-15s | %-30s |\n\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
							}
							mysql_free_result(sql_result);
						}
						printf("\n");
					}
				}
			}
			else if (type_num == 0)
			{
				main_flag = true;
				continue;
			}
			else
			{
				printf("Didn't i ask you to enter only one number???? \n");
				continue;
			}
		}
	}
	char clear[100] = "drop table Customer, Package, Transport, Shipping, attribute, Bill";
	mysql_query(connection, clear);
	mysql_close(connection);
	return 0;
}




/*

	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t6. TYPE 6\n");
	printf("\t7. TYPE 7\n");
	printf("\t0. QUIT\n");
	//printf("----------------------------------\n");
	printf("\n\n");
	printf("---- TYPE 5 ----\n\n");
	printf("** Find the top k brands by unit sales by the year**\n");
	printf(" Which K? : 3\n");

	return 0;

}
*/