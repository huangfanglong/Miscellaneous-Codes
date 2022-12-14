DROP TABLES ORDERS;
DROP TABLES ORDERS_SHIP_CUSTOMERS;
DROP TABLES CART_ENTRY;
DROP TABLES INVENTORY;
DROP TABLES CUSTOMERS;
DROP TABLES CHECKOUT;
DROP TABLES CHARGES;

CREATE TABLE IF NOT EXISTS CUSTOMERS
(
    CUSTOMER_ID             INT(10),
    NAME_                   VARCHAR(30) NOT NULL,
    EMAIL                   VARCHAR(30) NOT NULL,
    CARD_NUMBER             VARCHAR(30) NOT NULL,
    MAILING                 VARCHAR(30) NOT NULL,

    PRIMARY KEY (CUSTOMER_ID)
);

CREATE TABLE IF NOT EXISTS CHECKOUT
(
    CHECKOUT_ID             INT(10) NOT NULL AUTO_INCREMENT,
    CUSTOMER_ID             INT(10) NOT NULL,
    CHARGES_USD             DECIMAL(50,2) NOT NULL,
    TOTAL_PRICE_USD         DECIMAL(50,2) NOT NULL,

    PRIMARY KEY (CHECKOUT_ID),
    FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMERS (CUSTOMER_ID)
);

CREATE TABLE IF NOT EXISTS INVENTORY
(
    PART_ID                 INT(10) NOT NULL AUTO_INCREMENT,
    RETAIL_PRICE_USD        DECIMAL(50,2) NOT NULL,
    PART_NAME               VARCHAR(30) NOT NULL,
    DESCRIPTION_            VARCHAR(100) NOT NULL,
    QUANTITY                INT(10) NOT NULL,
    WEIGHT_LBS              INT(10),

    PRIMARY KEY (PART_ID)
);

CREATE TABLE IF NOT EXISTS ORDERS
(
    ORDER_ID                INT(10) NOT NULL AUTO_INCREMENT,
    CUSTOMER_ID             INT(10) NOT NULL,
    ORDER_STATUS            CHAR(30) NOT NULL,
    ORDER_TOTAL_USD         DECIMAL(50,2),

    PRIMARY KEY (ORDER_ID),
    FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMERS (CUSTOMER_ID)
);

CREATE TABLE IF NOT EXISTS CART_ENTRY
(
    ENTRY_ID                INT(10) AUTO_INCREMENT,
    CUSTOMER_ID             INT(10) NOT NULL,
    PART_ID                 INT(10) NOT NULL, 
    PRODUCT_QUANTITY        INT(10) NOT NULL,
    TOTAL_USD               DECIMAL(50,2),

    PRIMARY KEY (ENTRY_ID),
    FOREIGN KEY (PART_ID) REFERENCES INVENTORY (PART_ID)
);

CREATE TABLE IF NOT EXISTS CHARGES
(
    CHARGE                  INT(10) AUTO_INCREMENT,
    WEIGHT_                 INT(10) NOT NULL,
    CHARGES_USD             DECIMAL(50,2) NOT NULL,

    PRIMARY KEY (CHARGE)
);

CREATE TABLE IF NOT EXISTS ORDERS_SHIP_CUSTOMERS
(
    ORDER_ID                INT(10) NOT NULL,
    CUSTOMER_ID             INT(10) NOT NULL,
    SHIP_DATE               DATETIME NOT NULL,

    PRIMARY KEY (ORDER_ID, CUSTOMER_ID),
    FOREIGN KEY (ORDER_ID) REFERENCES ORDERS (ORDER_ID),
    FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMERS (CUSTOMER_ID)
);


----TOTALS, SHIPPING AND HANDLING----
INSERT INTO CHARGES
    (CHARGE,WEIGHT_,CHARGES_USD)
	VALUES('1','20.00','12.00');

INSERT INTO CHARGES
    (CHARGE,WEIGHT_,CHARGES_USD)
	VALUES('2','60.00','32.00');

INSERT INTO CHARGES
    (CHARGE,WEIGHT_,CHARGES_USD)
	VALUES('3','110.00','59.00');

----PRODUCT INSERTS----
INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('50.95','Tire',' Rubber tires for all weather use.','56','20');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('212.00','Rim','Metal alloy chrome rims.','56','20');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('119.99','Radiator','Heat sink for the engine.','40','10');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('89.99','Air Intake','Cold air intake for increases fuel ratio.','35','10');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('350.00','Exhaust','Dual pipe titanium tipped exaust pipes.','10','15');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('235.95','Headers','Long tube headers.','35','5');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('75.00','Manifold','Premium Exaust delivery system','50','7');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('12.99','Spark Plug','Rapid start spark plugs','200','1');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('20.00','Brake pads','Rapid cooling race brake pads','90','4');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('32.99','Headlight','Bright high beam headlight','25','2');

INSERT INTO INVENTORY
    (RETAIL_PRICE_USD,PART_NAME,DESCRIPTION_,QUANTITY,WEIGHT_LBS)
	VALUES('140.00','Seats','Leather interior seats','0','8');
