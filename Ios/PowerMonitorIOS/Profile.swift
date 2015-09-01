//
//  Profile.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 06/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

let D_POLLING_MIN_VAL = 1
let D_POLLING_MAX_VAL = (60 * 24) /* //TODO */ * 10
let D_POLLING_STEP_VAL = 1
let D_DEFAULT_PROFILE_NAME = "newProfile"
let D_DEFAULT_PROFILE_POLL = D_POLLING_MIN_VAL

struct Profile
{
	//Profile infos
	var id: Int
	var name: String
	//Profile settings
	var polling: Int
	var timeSlots: [TimeSlot]!
	var alertes: [Alerte]!
}

// convert JSON profile's data into Profile struct 
//  (the basic one without alert or timeslots)
func generateProfileFromJSON(data: JSON) -> Profile
{
	var profile: Profile

	profile = Profile(id: data["id"].intValue,
		name: data["name"].stringValue,
		polling: data["polling"].intValue,
		timeSlots: nil,
		alertes: nil)
	return profile
}

func generateTimeSlotsFromJSON(data: JSON) -> [TimeSlot] {
	var timeSlots = [TimeSlot]()

	for element in data as JSON {
		timeSlots.append(generateTimeSlotFromJSON(element.1))
	}
	return timeSlots
}

func generateAlertsFromJSON(data: JSON) -> [Alerte] {
	return [Alerte]()
}