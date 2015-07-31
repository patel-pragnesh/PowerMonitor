//
//  Session.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 06/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

struct Session
{
	var userId: Int
	var token: String
}

/*
** Extract a session from JSON Data 
*/
func generateSessionFromJSON(sessionJSON: JSON) -> Session
{
	var session: Session

	session = Session(userId: sessionJSON["userId"].intValue,
		token: sessionJSON["token"].stringValue)
	return session
}