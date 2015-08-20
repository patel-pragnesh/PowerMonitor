//
//  Network.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 25/02/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation
import SwiftyJSON

//TODO faire une gestion d'erreur a base de token, genre si les token sont wrong
// demander une reco ou quoi

// Singleton
private let networkSI = Network()

class Network {
	var _proto = Protocol()
	var _jReq = JSONRequest()
	var _currentSession: Session? = nil

	// Singleton init
	class var sharedInstance: Network {
		return networkSI
	}

	/* ------------------------------------------------------------------------ */

	// Connect sockets streams to host:port
	func connect(host: String, port: Int) {
		_proto.connect(host, port: port)
	}

	// Close the current socket streams
	func disconnect() {
		_proto.disconnect()
	}

	/* ------------------------------------------------------------------------ */

	/*
	** If socket not connected return nil
	** else if success return D_REQUEST_SUCCESS
	** else return errCode
	*/
	func login(mail: String, password: String) -> Int? {
		var returnCode: Int = -1
		var loginReq :JSON
		var loginRes :NSData
		var res: (returnCode: Int, session: Session?)

		if !_proto.isConnected() {
			return nil
		}
		loginReq = _jReq.getLogin(mail, passwd: password)
		_proto.writePaquet(loginReq)
		let resJSON = JSON(data: _proto.readPacket())
		returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		_currentSession = generateSessionFromJSON(resJSON["session"])
		return (returnCode)
	}

	// retrieve modulesJSON from server
	func getModules() -> (returnCode: Int, modulesJSON: JSON) {
		var returnCode: Int = -1
		var modulesJSON: JSON!

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getGetModules(_currentSession!))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
			modulesJSON = resJSON["modules"]
		}
		return (returnCode, modulesJSON)
	}

	// return all the details over a particular module
	func getModuleDetails(moduleId: Int, timeFrame: (beg: Int, end: Int)) {

	}

	// request to update a module's name
	func setModuleName(id: Int, newName: String) -> Int {
		var returnCode: Int = -1
		var moduleNameJSON: JSON!

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getSetModuleName(_currentSession!, id: id, newName: newName))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return returnCode
	}

	// set state of corresponding module('id') to 'status'
	func turnOnOff(status: Bool, id: Int) -> Int {
		var returnCode: Int = -1
		var turnOnOffJSON: JSON!

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getTurnOnOff(_currentSession!, id: id, status: status))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return returnCode
	}

	// retrieve profilesJSON from server
	func getProfiles() -> (returnCode: Int, profilesJSON: JSON) {
		var returnCode: Int = -1
		var profilesJSON: JSON!

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getGetProfiles(_currentSession!))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
			profilesJSON = resJSON["profiles"]
		}
		return (returnCode, profilesJSON)
	}

	// add a new profile
	func addProfile(name: String, polling: Int) -> (returnCode: Int, id: Int)
	{
		var returnCode: Int = -1
		var profileId: Int = -1;

		if _currentSession != nil {
			println((_jReq.getAddProfile(_currentSession!, name: name, polling: polling)).description) //DEV
			_proto.writePaquet(_jReq.getAddProfile(_currentSession!, name: name, polling: polling))
			let resJSON = JSON(data: _proto.readPacket())
			println(resJSON.description) //DEV
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
			if returnCode > 0
			{
				profileId = resJSON["profileId"].intValue
			}
		}
		return (returnCode, profileId)
	}

	// delette an existing profile
	func deleteProfile(id: Int) -> Int
	{
		var returnCode: Int = -1

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getDeleteProfile(_currentSession!, id: id))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return (returnCode)
	}

	// update corresponding profile polling value
	func updateProfilePolling(id: Int, polling: Int) -> Int {
		var returnCode: Int = -1

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getUpdateProfilePolling(_currentSession!, id: id, polling: polling))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return (returnCode)
	}

	// retrieve profileJSON from server
	func getProfile(id: Int) -> (returnCode: Int, profileJSON: JSON) {
		var returnCode: Int = -1
		var profileJSON: JSON! //TODO : pas safe

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getGetProfile(_currentSession!, id: id))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
			profileJSON = resJSON["profile"]
		}
		return (returnCode, profileJSON)
	}

	// ajoute un timeslot
	func addTimeSlot(profileId: Int, timeslot: TimeSlot) -> Int {
		var returnCode: Int = -1

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getAddTimeSlot(_currentSession!, profileId: profileId, timeslot: timeslot))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return (returnCode)
	}

	func updateTimeSlot(timeslot: TimeSlot) -> Int {
		var returnCode: Int = -1

		if _currentSession != nil {
			_proto.writePaquet(_jReq.getModifyTimeSlot(_currentSession!, timeslot: timeslot))
			let resJSON = JSON(data: _proto.readPacket())
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return (returnCode)
	}

	func deleteTimeSlot(timeslotId: Int) -> Int {
		var returnCode: Int = -1

		if _currentSession != nil {
			println("SEND " + _jReq.getDeleteTimeSlot(_currentSession!, id: timeslotId).description) //DEV
			_proto.writePaquet(_jReq.getDeleteTimeSlot(_currentSession!, id: timeslotId))
			let resJSON = JSON(data: _proto.readPacket())
			println("RES " + resJSON.description) //DEV
			_currentSession = generateSessionFromJSON(resJSON["session"])
			returnCode = generateReturnCodeFromJSON(resJSON["returnCode"])
		}
		return (returnCode)
	}

}