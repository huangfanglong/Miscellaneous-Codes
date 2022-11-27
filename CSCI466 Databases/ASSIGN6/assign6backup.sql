#1
DROP TABLE IF EXISTS Visit, Dog;

#2
CREATE TABLE Dog(
	DogID	INT(9)		NOT NULL AUTO_INCREMENT,
	Breed	VARCHAR(30)	NOT NULL,					 
	Name		VARCHAR(20)	NOT NULL,					
	Weight	VARCHAR(6)	NOT NULL,

	PRIMARY KEY (DogID)		
);

#3
INSERT INTO Dog				
	VALUES(	'123456789',		# ID
			'Husky',			# Breed
			'Joe',			# Name
			'50kg'	);		# Weight
INSERT INTO Dog
	VALUES(	'987654321',		# ID
			'Bulldog',		# Breed
			'Mama',			# Name
			'61.5kg'	);		# Weight
INSERT INTO Dog
	VALUES(	'564782945',		# ID
			'German Shepherd',	# Breed
			'So',			# Name
			'52kg'	);		# Weight
INSERT INTO Dog
	VALUES(	'823954710',		# ID
			'Alaskan Malamute',	# Breed
			'Haha',			# Name
			'35kg'	);		# Weight
INSERT INTO Dog
	VALUES(	'525845691',		# ID
			'Dobermann',		# Breed
			'JayK',			# Name
			'39.9kg'	);		# Weight
INSERT INTO Dog
	VALUES(	'758451920',		# ID
			'Pomeranian',		# Breed
			'Fat',			# Name
			'2.49kg'	);		# Weight

#4
DESCRIBE Dog;

#5
SELECT * FROM Dog;

#6
CREATE TABLE Visit(	
	VisitID	INT(9)	NOT NULL AUTO_INCREMENT,	# PRIMARY KEY
	DogID	INT(9)	NOT NULL,			# FOREIGN KEY
	Date		TIMESTAMP	NOT NULL,			# TIME OF THE VISIT
	
	PRIMARY KEY (VisitID),
	FOREIGN KEY (DogID) REFERENCES Dog(DogID)
);

#7	
INSERT INTO Visit
	VALUES(	'000000001',					# Visit ID
			'758451920',					# Dog ID
			'2022-01-15 09:12:01'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000002',					# Visit ID
			'758451920',					# Dog ID
			'2022-01-16 15:55:24'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000003',					# Visit ID
			'564782945',					# Dog ID
			'2022-01-16 19:42:19'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000004',					# Visit ID
			'123456789',					# Dog ID
			'2022-01-25 07:05:59'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000005',					# Visit ID
			'987654321',					# Dog ID
			'2022-01-27 14:11:02'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000006',					# Visit ID
			'823954710',					# Dog ID
			'2022-01-28 11:59:09'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000007',					# Visit ID
			'525845691',					# Dog ID
			'2022-01-28 12:02:00'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000008',					# Visit ID
			'758451920',					# Dog ID
			'2022-01-28 12:02:00'	);		# Time of the visit	
INSERT INTO Visit
	VALUES(	'000000009',					# Visit ID
			'823954710',					# Dog ID
			'2022-02-02 08:04:55'	);		# Time of the visit	

#8
DESCRIBE Visit;

#9
SELECT * FROM Visit;

#10
ALTER TABLE Visit ADD Bill CHAR(10);

#11
UPDATE Visit
	SET Bill = '$51.25'
	WHERE VisitID = 000000001;
UPDATE Visit
	SET Bill = '$51.25'
	WHERE VisitID = 000000002;
UPDATE Visit
	SET Bill = '$51.25'
	WHERE VisitID = 000000003;
UPDATE Visit
	SET Bill = '$99.89'
	WHERE VisitID = 000000004;
UPDATE Visit
	SET Bill = '$25.00'
	WHERE VisitID = 000000005;
UPDATE Visit
	SET Bill = '$67.54'
	WHERE VisitID = 000000006;
UPDATE Visit
	SET Bill = '$51.25'
	WHERE VisitID = 000000007;
UPDATE Visit
	SET Bill = '$51.25'
	WHERE VisitID = 000000008;
UPDATE Visit
	SET Bill = '$99.89'
	WHERE VisitID = 000000009;

SELECT * FROM Visit;