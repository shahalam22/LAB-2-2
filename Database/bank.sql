-- CREATE USER bank IDENTIFIED BY bank;
-- GRANT dba TO bank;
-- CONNECT BANK;

DROP TABLE BORROWER;
DROP TABLE DEPOSITOR;
DROP TABLE ACCOUNT;
DROP TABLE LOAN;
DROP TABLE CUSTOMER;
DROP TABLE BRANCH;

CREATE TABLE BRANCH (
    BRANCH_NAME VARCHAR(20),
    BRANCH_CITY VARCHAR(20),
    ASSETS INT,
    CONSTRAINT BRANCH_PK PRIMARY KEY (BRANCH_NAME)
);

-- DESCRIBE BRANCH;

CREATE TABLE CUSTOMER (
    CUSTOMER_NAME VARCHAR(20),
    CUSTOMER_STREET VARCHAR(20),
    CUSTOMER_CITY VARCHAR(20),
    CONSTRAINT CUSTOMER_PK PRIMARY KEY (CUSTOMER_NAME)
);

-- DESCRIBE CUSTOMER;

CREATE TABLE ACCOUNT (
    ACCOUNT_NUMBER VARCHAR(10),
    BRANCH_NAME VARCHAR(20),
    BALANCE INT,
    CONSTRAINT ACCOUNT_PK PRIMARY KEY (ACCOUNT_NUMBER),
    CONSTRAINT ACCOUNT_FK FOREIGN KEY (BRANCH_NAME) REFERENCES BRANCH (BRANCH_NAME)
);

-- DESCRIBE ACCOUNT;

CREATE TABLE LOAN (
    LOAN_NUMBER VARCHAR(10),
    BRANCH_NAME VARCHAR(20),
    AMOUNT INT,
    CONSTRAINT LOAN_PK PRIMARY KEY (LOAN_NUMBER),
    CONSTRAINT LOAN_FK FOREIGN KEY (BRANCH_NAME) REFERENCES BRANCH (BRANCH_NAME)
);

-- DESCRIBE LOAN;

CREATE TABLE DEPOSITOR (
    CUSTOMER_NAME VARCHAR(20),
    ACCOUNT_NUMBER VARCHAR(10),
    CONSTRAINT DEPOSITOR_PK PRIMARY KEY (CUSTOMER_NAME, ACCOUNT_NUMBER),
    CONSTRAINT DEPOSITOR_FK1 FOREIGN KEY (CUSTOMER_NAME) REFERENCES CUSTOMER (CUSTOMER_NAME),
    CONSTRAINT DEPOSITOR_FK2 FOREIGN KEY (ACCOUNT_NUMBER) REFERENCES ACCOUNT (ACCOUNT_NUMBER)
);

-- DESCRIBE DEPOSITOR;

CREATE TABLE BORROWER (
    CUSTOMER_NAME VARCHAR(20),
    LOAN_NUMBER VARCHAR(10),
    CONSTRAINT BORROWER_PK PRIMARY KEY (CUSTOMER_NAME, LOAN_NUMBER),
    CONSTRAINT BORROWER_FK1 FOREIGN KEY (CUSTOMER_NAME) REFERENCES CUSTOMER (CUSTOMER_NAME),
    CONSTRAINT BORROWER_FK2 FOREIGN KEY (LOAN_NUMBER) REFERENCES LOAN (LOAN_NUMBER)
);

-- DESCRIBE BORROWER;

-- INSERTING VALUES IN BRANCH TABLE
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Brighton', 'Brooklyn', 7100000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Downtown', 'Brooklyn', 9000000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Mianus', 'Horseneck', 400000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('North Town', 'Rye', 3700000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Perryridge', 'Horseneck', 1700000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Pownal', 'Bennington', 300000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Redwood', 'Palo Alto', 2100000);
INSERT INTO BRANCH (BRANCH_NAME, BRANCH_CITY, ASSETS) VALUES ('Round Hill', 'Horseneck', 8000000);


-- INSERTING VALUES IN CUSTOMER TABLE
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Adams', 'Spring', 'Pittsfield');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Brooks', 'Senator', 'Brooklyn');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Curry', 'North', 'Rye');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Glenn', 'Sand Hill', 'Woodside');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Green', 'Walnut', 'Stamford');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Hayes', 'Main', 'Harrison');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Johnson', 'Alma', 'Palo Alto');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Jones', 'Main', 'Harrison');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Lindsay', 'Park', 'Pittsfield');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Smith', 'North', 'Rye');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Turner', 'Putnam', 'Stampford');
INSERT INTO CUSTOMER (CUSTOMER_NAME, CUSTOMER_STREET, CUSTOMER_CITY) VALUES ('Williams', 'Nassau', 'Princeton');


-- INSERTING VALUES IN ACCOUNT TABLE
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-101', 'Downtown', 500);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-102', 'Perryridge', 400);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-201', 'Brighton', 900);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-215', 'Mianus', 700);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-217', 'Brighton', 750);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-222', 'Redwood', 700);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-305', 'Round Hill', 350);
INSERT INTO ACCOUNT (ACCOUNT_NUMBER, BRANCH_NAME, BALANCE) VALUES ('A-322', 'Perryridge', 500);


-- INSERTING VALUES IN LOAN TABLE
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-11', 'Round Hill', 900);
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-14', 'Downtown', 1500);
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-15', 'Perryridge', 1500);
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-16', 'Perryridge', 1300);
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-17', 'Downtown', 1000);
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-23', 'Redwood', 2000);
INSERT INTO LOAN (LOAN_NUMBER, BRANCH_NAME, AMOUNT) VALUES ('L-93', 'Mianus', 500);


-- INSERTING VALUES IN DEPOSITOR TABLE
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Hayes', 'A-102');
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Johnson', 'A-101');
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Johnson', 'A-201');
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Jones', 'A-217');
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Adams', 'A-322');
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Smith', 'A-215');
INSERT INTO DEPOSITOR (CUSTOMER_NAME, ACCOUNT_NUMBER) VALUES ('Turner', 'A-305');


-- INSERTING VALUES IN BORROWER TABLE
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Adams', 'L-16');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Curry', 'L-93');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Hayes', 'L-15');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Glenn', 'L-14');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Jones', 'L-17');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Smith', 'L-11');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Smith', 'L-23');
INSERT INTO BORROWER (CUSTOMER_NAME, LOAN_NUMBER) VALUES ('Williams', 'L-17');

