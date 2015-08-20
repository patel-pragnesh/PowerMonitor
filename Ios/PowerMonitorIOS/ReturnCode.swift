//
//  ReturnCode.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 05/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

let D_REQUEST_FAILURE: Int			= -1
let D_REQUEST_SUCCESS: Int			= 0

/*
** Enum for erros => (retCode, Description)
**
** 0x1xx -> Generic errors (can't fetch data, invalid token...)
** 0x2xx -> Erreurs login (invalid user/pwd...)
** 0x3xx -> Erreurs modules (status, name...)
** 0x4xx -> Erreurs profiles (delete, add...)
*/

let D_STATE_ALREADY_SET:Int	= 0x402

func errDesc(returnCode: Int) -> String {
	switch returnCode {
	//Application networking error
	case -1:
		return "Data reception problem"
	//General errors
	case 0x101:
		return "Not well formatted request"
	case 0x102:
		return "Command not found"
	case 0x103:
		return "Invalid expression"
	case 0x104:
		return "Session expired"
	//Authentication errors
	case 0x201:
		return "Incorrect password"
	//User
	case 0x301:
		return "User not found"
	//Module
	case 0x401:
		return "Module not found"
	case 0x402:
		return "Cannot update module state"
	case 0x403:
		return "Module already in given state"
	//Profile
	case 0x501:
		return "Profile not found"
	case 0x502:
		return "Profile still in use"
	case 0x503:
		return "Profile name already exist"
	//Alert
	case 0x601:
		return "Alert not found"
	//Timeslot
	case 0x701:
		return "Timeslot not found"
	//Unit
	case 0x801:
		return "Unit not found"
	default:
		return "No error"
	}
}

/*
** Verify is JSON contain a proper returncode then return it
** or return D_REQUEST_FAILURE if
*/
func generateReturnCodeFromJSON(returnCodeJSON: JSON) -> Int {
	var returnCode: Int = D_REQUEST_FAILURE

	if let rc = returnCodeJSON.int {
		returnCode = rc
	}
	return returnCode
}