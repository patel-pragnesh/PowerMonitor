//
//  ModuleDetails.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 28/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

class ModuleDetails {
	private var _network = Network.sharedInstance

	func editName(moduleId: Int, newName: String) -> alertViewContent? {
		var ret: alertViewContent!

		let reqRet = _network.setModuleName(moduleId, newName: newName)
		if (reqRet != D_REQUEST_SUCCESS) {
			ret = ("Name editing Failed", errDesc(reqRet), "Ok")
		}
		return ret
	}
	
}
