//
//  JSONRequest.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 23/02/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation
import SwiftyJSON

// JSON Request
let D_JSON_LOGIN: JSON					= ["cmd":"login", "email":"", "password":""]
let D_JSON_GETMODULES: JSON			= ["cmd":"getModules","session":["userId":"","token":""]]
let D_JSON_SETMODULENAME: JSON	= ["cmd":"renameModule","name":"","id":"","session":["userId":"","token":""]]
let D_JSON_TURNONOFF: JSON			=	["cmd":"turnOnOff","status":"","id":"","session":["userId":"","token":""]]

let D_JSON_GETPROFILES: JSON		= ["cmd":"getProfiles","session":["userId":"","token":""]]
let D_JSON_ADDPROFILE: JSON			=	["cmd":"addProfile","name":"","polling":"","session":["userId":"","token":""]]
let D_JSON_DELETEPROFILE: JSON	=	["cmd":"deleteProfile","id":"","session":["userId":"","token":""]]
let D_JSON_UPDATEPOLLING: JSON	=	["cmd":"updateProfilePolling","id":"","polling":"","session":["userId":"","token":""]]
let D_JSON_GETPROFILE: JSON			= ["cmd":"getProfile","id":"","session":["userId":"","token":""]]
let D_JSON_GETMODULECONSO: JSON = ["cmd":"getModuleConso","moduleId":"","beg":"","end":"","unitId":"","session":["userId":"","token":""]]

let D_JSON_ADDTIMESLOT: JSON		= ["cmd":"addTimeSlot","profileId":"","beg":["day":"","minute":""],"end":["day":"","minute":""],"session":["userId":"","token":""]]
let D_JSON_MODIFYTIMESLOT: JSON = ["cmd":"updateTimeSlot","id":"","beg":["day":"","minute":""],"end":["day":"","minute":""],"session":["userId":"","token":""]]
let D_JSON_DELETETIMESLOT: JSON = ["cmd": "deleteTimeSlot","id":"","session":["userId":"","token":""]]

let D_JSON_CUSRN: JSON					= ["cmd":"change_username","userid":"","username":""]
let D_JSON_CPWD: JSON						= ["cmd":"change_password","userid":"","password":""]
let D_JSON_NACC: JSON						= ["cmd":"new_account","userid":"","username":"","password":""]

class JSONRequest {

	// Return request for login/email authentification
	func getLogin(email: String, passwd: String) -> JSON {
		var json: JSON = D_JSON_LOGIN

		json["email"] = JSON(email)
		json["password"] = JSON(passwd)
		return (json)
	}

	// Return request for getting the modules list
	func getGetModules(session: Session) -> JSON {
		var json: JSON = D_JSON_GETMODULES

		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// return request for changing module's name
	func getSetModuleName(session: Session, id: Int, newName: String) -> JSON {
		var json: JSON = D_JSON_SETMODULENAME

		json["name"] = JSON(newName)
		json["id"] = JSON(id)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// return request for changing module's state
	func getTurnOnOff(session: Session, id: Int, status: Bool) -> JSON {
		var json: JSON = D_JSON_TURNONOFF

		json["status"] = JSON(status)
		json["id"] = JSON(id)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// Return request for getting the profiles list
	func getGetProfiles(session: Session) -> JSON {
		var json: JSON = D_JSON_GETPROFILES

		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// Return request for adding a new profile
	func getAddProfile(session: Session, name: String, polling: Int) -> JSON {
		var json: JSON = D_JSON_ADDPROFILE

		json["name"] = JSON(name)
		json["polling"] = JSON(polling)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// Return request for delete an existing profile
	func getDeleteProfile(session: Session, id: Int) -> JSON {
		var json: JSON = D_JSON_DELETEPROFILE

		json["id"] = JSON(id)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// Return request for updating corresponding profile polling value
	func getUpdateProfilePolling(session: Session, id: Int, polling: Int) -> JSON {
		var json: JSON = D_JSON_UPDATEPOLLING

		json["id"] = JSON(id)
		json["polling"] = JSON(polling)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	// Return request for getting a profile info
	func getGetProfile(session: Session, id: Int) -> JSON {
		var json: JSON = D_JSON_GETPROFILE

		json["id"] = JSON(id)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	func getAddTimeSlot(session: Session, profileId: Int, timeslot: TimeSlot) -> JSON {
		var json: JSON = D_JSON_ADDTIMESLOT

		json["profileId"] = JSON(profileId)
		json["beg"]["day"] = JSON(timeslot.beg.day)
		json["beg"]["minute"] = JSON(timeslot.beg.min)
		json["end"]["day"] = JSON(timeslot.end.day)
		json["end"]["minute"] = JSON(timeslot.end.min)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	func getModifyTimeSlot(session: Session, timeslot: TimeSlot) -> JSON {
		var json: JSON = D_JSON_MODIFYTIMESLOT

		json["id"] = JSON(timeslot.id)
		json["beg"]["day"] = JSON(timeslot.beg.day)
		json["beg"]["minute"] = JSON(timeslot.beg.min)
		json["end"]["day"] = JSON(timeslot.end.day)
		json["end"]["minute"] = JSON(timeslot.end.min)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	func getDeleteTimeSlot(session: Session, id: Int) -> JSON {
		var json: JSON = D_JSON_DELETETIMESLOT

		json["id"] = JSON(id)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}

	func getModuleConso(session: Session, moduleId: Int, beg: Int, end: Int, unitId: Int) -> JSON {
		var json: JSON = D_JSON_GETMODULECONSO

		json["moduleId"] = JSON(moduleId)
		json["beg"] = JSON(beg)
		json["end"] = JSON(end)
		json["unitId"] = JSON(unitId)
		json["session"]["userId"] = JSON(session.userId)
		json["session"]["token"] = JSON(session.token)
		return (json)
	}
}