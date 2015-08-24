//
//  Module.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 23/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

struct Module {
	//Module Info
	var id: Int
	var name: String
	var serial: Int
	var status: Bool
	//Profile
	var defaultProfileId: Int!
	var defaultProfileName: String!
	var internalProfileId: Int
}

// convert JSON module's list request data into Module struct
func generateModuleFromJSON(data: JSON) -> Module {
	var defaultProfile = generateProfileFromJSON(data["defaultProfile"])
	var status = (data["status"].stringValue == "true")
	var newModule = Module(id: data["id"].intValue,
		name: data["name"].stringValue,
		serial: data["serialNumber"].intValue,
		status: status,
		defaultProfileId: data["defaultProfile"]["id"].int,
		defaultProfileName: data["defaultProfile"]["name"].string,
		internalProfileId: data["internProfilId"].intValue)
	return newModule
}