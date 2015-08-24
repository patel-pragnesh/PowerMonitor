//
//  ComonUtils.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 09/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation

/*
** Check the userEnv to see if user is logged in
*/
func isUserLogged() -> Bool
{
	let prefs = NSUserDefaults.standardUserDefaults()
	let isLoggedIn = prefs.integerForKey("ISLOGGEDIN") as Int

	if (isLoggedIn != 1)
	{
		return false
	}
	return true
}