/*
** Unit
*/
INSERT	INTO `Unit` (`id`,      `name`, `symbol`)
	VALUES	    (   1, 'Puissance',      'W'),
		    (	2, 'Intensité',      'A'),
		    (	3,   'Voltage',      'V');

/*
** Profile
*/
INSERT	INTO `Profile` (`id`,          `typeid`, `polling`)
	VALUES	       (   1, 'InternalProfile',      1800), /* TV */
		       (   2, 'InternalProfile',       900), /* Frigo */
		       (   3,  'DefaultProfile',      3600), /* Vacances */
		       (   4,  'DefaultProfile',       600); /* Semaine */

/*
** DefaultProfile
*/
INSERT	INTO `DefaultProfile` (`id`,     `name`)
	VALUES		      (   3, 'Vacances'),
			      (   4,  'Semaine');

/*
** InternalProfile
*/
INSERT	INTO `InternalProfile` (`id`)
	VALUES		       (   1),
			       (   2);

/*
** TimeSlot
*/

INSERT	INTO `TimeSlot` (`id`,   `beg_day`, `beg_minute`,   `end_day`, `end_minute`, `profile`)
	VALUES		(   1,    'Monday',          360,    'Monday',          480,         4), /* Semaine */
			(   2,   'Tuesday',          360,   'Tuesday',          480,         4),
			(   3, 'Wednesday',          360, 'Wednesday',          480,         4),
			(   4,  'Thursday',          360,  'Thursday',          480,         4),
			(   5,    'Friday',          360,    'Friday',          480,         4),
			(   6,    'Monday',          960,    'Monday',         1260,         4),
			(   7,   'Tuesday',          960,   'Tuesday',         1260,         4),
			(   8, 'Wednesday',          960, 'Wednesday',         1260,         4),
			(   9,  'Thursday',          960,  'Thursday',         1260,         4),
			(  10,    'Friday',          960,    'Friday',         1260,         4),
			(  11,  'Saturday',	     600,  'Saturday',	       1320,	     1), /* TV */
			(  12,    'Sunday',	     600,    'Sunday',	       1320,	     1);

/*
** User
*/
INSERT	INTO `User` (`id`,      `name`,   `surname`,                          `email`,                                                                                                `hash`,                  `salt`)
	VALUES	    (   1,    'Alexis',    'Mestag',       'alexis.mestag@epitech.eu', UNHEX(SHA2(concat(   'alexis', UNHEX('7b471f84169e7d56f8da82ac2ba8c5e8b431345b732c453b1270c937732a8fa2')), 256)),
		    	      		   		   			       			              UNHEX('7b471f84169e7d56f8da82ac2ba8c5e8b431345b732c453b1270c937732a8fa2')), /* Password: alexis */
		    (   2,     'Cyril',  'Jourdain',      'cyril.jourdain@epitech.eu', UNHEX(SHA2(concat(    'cyril', UNHEX('5b6fa0817424618a9d13f0d9dec76c5642f80a6ed2b4c35670aa8f8e7fc923c8')), 256)),
		    	       		 		  			       			     	      UNHEX('5b6fa0817424618a9d13f0d9dec76c5642f80a6ed2b4c35670aa8f8e7fc923c8')), /* Password: cyril */
		    (   3,   'Gregory',      'Neut',        'gregory.neut@epitech.eu', UNHEX(SHA2(concat(  'gregory', UNHEX('7b471f84169e7d56f8da82ac2ba8c5e8b431345b732c453b1270c937732a8fa2')), 256)),
		    	     		     		    			       			   	      UNHEX('7b471f84169e7d56f8da82ac2ba8c5e8b431345b732c453b1270c937732a8fa2')), /* Password: gregory */
		    (	4, 'Guillaume', 'Marescaux', 'guillaume.marescaux@epitech.eu', UNHEX(SHA2(concat('guillaume', UNHEX('8d38f71e35266cb097f122a9f5f5609e4b0f9f5863edbcb3f9ab316453122ed3')), 256)),
		    	   			     				       				      UNHEX('8d38f71e35266cb097f122a9f5f5609e4b0f9f5863edbcb3f9ab316453122ed3')), /* Password: guillaume */
		    (	5, 'Alexandre', 'Camilleri', 'alexandre.camilleri@epitech.eu', UNHEX(SHA2(concat('alexandre', UNHEX('a09ccf3f569936c02d373443d3922a9ecf425c14af137f7ef407f72385e22c1e')), 256)),
		    	   			     				       				      UNHEX('a09ccf3f569936c02d373443d3922a9ecf425c14af137f7ef407f72385e22c1e')), /* Password: alexandre */
		    (	6,   'Antoine',    'Maitre',      'antoine.maitre@epitech.eu', UNHEX(SHA2(concat(  'antoine', UNHEX('d4560a485d397f5e26a23092622f52fb35913d82065f5a363110138e5c941963')), 256)),
		    	     		   		  			       			              UNHEX('d4560a485d397f5e26a23092622f52fb35913d82065f5a363110138e5c941963')), /* Password: antoine */
		    (	7,   'Laurent',     'Ansel',       'laurent.ansel@epitech.eu', UNHEX(SHA2(concat(  'laurent', UNHEX('9be13e17702d4a4d2133b9eca002cb710f2c92a8bf5de0851ae73e5a28aa1506')), 256)),
		    	     		    		   			       			              UNHEX('9be13e17702d4a4d2133b9eca002cb710f2c92a8bf5de0851ae73e5a28aa1506')); /* Password: laurent */

/*
** Alerts
*/
INSERT	INTO `Alert` (`id`, `information_value`, `information_unit`, `profile`)
	VALUES	     (   1,                  10,                  2,         1), /* 10A */
		     (   2,               15000,		  1,         2), /* 15kW */
		     (   3,                2000,		  3, 	     1), /* 2kV */
		     (   4,                  20,		  2, 	     2); /* 20A */

/*
** SlaveModule 
*/
INSERT	INTO `SlaveModule` (`id`,  `name`, `serialNumber`, `status`, `defaultProfile`, `internalProfile`)
	VALUES		   (   1,    'TV',         '0001',        1,             NULL,                 1),
			   (   2, 'Frigo', 	   '0002', 	  1,                3,                 2);
