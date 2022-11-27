DROP TABLE IF EXISTS SP, S, P;

CREATE TABLE S(
	S		INT(3)		NOT NULL AUTO_INCREMENT,
	SNAME	VARCHAR(30)	NOT NULL,					 
	STATUS	VARCHAR(20)	NOT NULL,					
	CITY	VARCHAR(6)		NOT NULL,

	PRIMARY KEY (S)		
);

INSERT INTO S				
	VALUES(	'1',
			'Smith',
			'20',
			'London'	);
INSERT INTO S				
	VALUES(	'2',
			'Jones',
			'10',
			'Paris'	);
INSERT INTO S				
	VALUES(	'3',
			'Blake',
			'30',
			'Paris'	);
INSERT INTO S				
	VALUES(	'4',
			'Clark',
			'20',
			'London'	);
INSERT INTO S				
	VALUES(	'5',
			'Adams',
			'30',
			'Athens'	);
			
CREATE TABLE P(
	P		INT(3)		NOT NULL AUTO_INCREMENT,
	PNAME	VARCHAR(5)	NOT NULL,					 
	COLOR	VARCHAR(5)	NOT NULL,					
	WEIGHT	VARCHAR(2)	NOT NULL,

	PRIMARY KEY (P)		
);

INSERT INTO P	
	VALUES(	'1',
			'Nut',
			'Red',
			'12'	);
INSERT INTO P
	VALUES(	'2',
			'Bolt',
			'Green',
			'17'	);
INSERT INTO P				
	VALUES(	'3',
			'Screw',
			'Blue',
			'17'	);
INSERT INTO P				
	VALUES(	'4',
			'Screw',
			'Red',
			'14'	);
INSERT INTO P				
	VALUES(	'5',
			'Cam',
			'Blue',
			'12'	);
INSERT INTO P				
	VALUES(	'6',
			'Cog',
			'Red',
			'19'	);

CREATE TABLE SP(	
	S		INT(3)		NOT NULL,
	P		INT(3)		NOT NULL,
	QTY		INT(3)		NOT NULL,
	
	PRIMARY KEY (S, P),
	FOREIGN KEY (S) REFERENCES S(S),
	FOREIGN KEY (P) REFERENCES P(P)
);

INSERT INTO SP
	VALUES(	'1',
			'1',
			'300'	);
INSERT INTO SP
	VALUES(	'1',
			'2',
			'200'	);
INSERT INTO SP
	VALUES(	'1',
			'3',
			'400'	);
INSERT INTO SP
	VALUES(	'1',
			'4',
			'200'	);
INSERT INTO SP
	VALUES(	'1',
			'5',
			'100'	);
INSERT INTO SP
	VALUES(	'1',
			'6',
			'100'	);
INSERT INTO SP
	VALUES(	'2',
			'1',
			'200'	);
INSERT INTO SP
	VALUES(	'2',
			'2',
			'400'	);
INSERT INTO SP
	VALUES(	'3',
			'2',
			'200'	);
INSERT INTO SP
	VALUES(	'4',
			'2',
			'200'	);
INSERT INTO SP
	VALUES(	'4',
			'4',
			'300'	);
INSERT INTO SP
	VALUES(	'4',
			'5',
			'400'	);