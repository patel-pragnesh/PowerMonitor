//
//  ProfileDetails.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 09/05/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

class ProfileDetails
{
	private var _network = Network.sharedInstance

	func editName(profileId: Int, newName: String) -> alertViewContent? { // TODO edit name of profile
		/*var ret: alertViewContent!

		let reqRet = _network.setProfileName(moduleId, newName: newName)
		if (reqRet != D_REQUEST_SUCCESS) {
			ret = ("Name editing Failed", errDesc(reqRet), "Ok")
		}
		return ret*/
		return nil
	}

	func deleteProfile(id: Int) -> alertViewContent? {
		var ret: alertViewContent!
		let reqRet = _network.deleteProfile(id)

		if (reqRet != D_REQUEST_SUCCESS) {
			ret = ("Deletion failed", errDesc(reqRet), "Ok")
		}
		return ret
	}

	func updatePolling(id: Int, polling: Int) -> alertViewContent? {
		var ret: alertViewContent!
		let reqRet = _network.updateProfilePolling(id, polling: polling)

		if (reqRet != D_REQUEST_SUCCESS) {
			ret = ("Couldn't update polling value", errDesc(reqRet), "Ok")
		}
		return ret
	}

	// retrieve the timeslots of a profile
	func getProfileTimeSlots(id: Int) -> (avc: alertViewContent?, timeSlots: [TimeSlot]) {
		var ret: alertViewContent!
		let reqRet = _network.getProfile(id)

		if (reqRet.returnCode != D_REQUEST_SUCCESS) {
			ret = ("Couldn't fetch the profile information from server", errDesc(reqRet.returnCode), "Ok")
		}
		println(reqRet.profileJSON.description) //TODO remove log
		return (ret, generateTimeSlotsFromJSON(reqRet.profileJSON["timeSlots"]))
	}

	// add a new timeslot to given profile
	func addNewTimeSlot(profileId: Int, timeslot: TimeSlot) -> alertViewContent? {
		var ret: alertViewContent!
		let res = _network.addTimeSlot(profileId, timeslot: timeslot)

		if (res != D_REQUEST_SUCCESS) {
			ret = ("Couldn't add the TimeSlot to profile", errDesc(res), "Ok")
		}
		return (ret)
	}

	func modifyExistingTimeSlot(timeslot: TimeSlot) -> alertViewContent? {
		var ret: alertViewContent!
		let res = _network.modifyTimeSlot(timeslot)

		if (res != D_REQUEST_SUCCESS) {
			ret = ("Couldn't modify the timeslot", errDesc(res), "Ok")
		}
		return (ret)
	}

	func deleteTimeSlot(timeslotId: Int) -> alertViewContent? {
		var ret: alertViewContent!
		let res = _network.deleteTimeSlot(timeslotId)

		if (res != D_REQUEST_SUCCESS) {
			ret = ("Couldn't delete the timeslot", errDesc(res), "Ok")
		}
		return (ret)
	}
}
