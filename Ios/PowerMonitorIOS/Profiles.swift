//
//  Profiles.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 23/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

class Profiles {
	private var _network = Network.sharedInstance
	private var _profiles = [Profile]()

	// return number of profiles inside Profiles
	func count() -> Int {
		return _profiles.count
	}

	// return Profile at Profiles[index]
	func at(index: Int) -> Profile {
		return _profiles[index]
	}

	// update Profiles with server Profiles - ret nil if no err
	func refresh() -> Int? {
		var res = _network.getProfiles()

		_profiles.removeAll()
		if res.returnCode != D_REQUEST_SUCCESS {
			return res.returnCode
		}
		append(res.profilesJSON)
		return nil
	}

	//create a new profile
	func addNew() -> Int {
		let res = _network.addProfile(D_DEFAULT_PROFILE_NAME, polling: D_DEFAULT_PROFILE_POLL)

		if (res.id != -1) {
			_profiles.append(Profile(id: res.id, name: D_DEFAULT_PROFILE_NAME, polling: D_DEFAULT_PROFILE_POLL, timeSlots: nil, alertes: nil))
		}
		return (res.returnCode)
	}

	/* ------------------------------------------------------------------------ */

	// append 1 or + Profile(s) struct(s) to Profiles from JSON
	private func append(newElementJSON: JSON) {
		for (index: String, profileJSON: JSON) in newElementJSON {
			var profile = generateProfileFromJSON(profileJSON)
			_profiles.append(profile)
		}
	}

	func append(newElement: Profile) {
		_profiles.append(newElement)
	}
}