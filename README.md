# CSE4110 Database system project
서강대학교 CSE4110 데이터베이스 시스템에서 실습한 프로젝트입니다.
## Project 1
### 프로젝트 설명
erwin 프로그램을 통해 개념적 스키마를 작성하는 프로젝트입니다.

택배 회사가 고객에게 택배를 배송하는 전 과정을 조회할 수 있는 스키마를 작성하는 것이 목표입니다.

프로젝트 2에서 구현할 때 용이하도록 정규화를 통해 데이터의 중복을 최소화하도록 구현했습니다.
### 과제 점수
Project 1  : 90 / 100

----------
## Project 2
### 프로젝트 설명
mysql workbench를 통해 Database를 논리적 스키마로 구축하였습니다.

이러한 데이터베이스에 쿼리를 날려 원하는 정보를 조회하거나 생성하는 c++ 프로그램을 작성하였습니다.
쿼리는 mysql문으로 작성하였습니다.

### Query 설명
Query 1-1 : 특정 트럭에서 충돌이 발생했다면, 그 시점에 트럭에 적재되어 있던 화물들을 보낸 고객 조회

Query 1-2 : 특정 트럭에서 충돌이 발생했다면, 그 시점에 트럭에 적재되어 있던 화물들을 받을 고객 조회

Query 1-3 : 특정 트럭에서 충돌이 발생했다면, 그 시점 이전에 배송 완료된 화물들을 조회

Query 2 : 특정 연도에 가장 많은 배송을 보낸 고객 조회

Query 3 : 특정 연도에 가장 많은 금액을 지불한 고객의 이름 조회

Query 4 : 기간 내에 배송되지 않은 배송 물품들을 전부 조회

Query 5 : 모든 고객의 특정 연월 명세서를 출력

### Data 생성
많은 데이터가 있어야 Query문이 정확하게 작동하는 지 파악할 수 있기 때문에,

일일히 data를 입력하기 보단, dummy data를 생성해주는 *[mockaroo](https://www.mockaroo.com/) 를 사용하였습니다.




