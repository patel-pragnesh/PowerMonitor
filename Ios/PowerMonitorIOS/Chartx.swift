//
//  Charts.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 30/08/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

class Chartx {
	private var _network = Network.sharedInstance

	func getModuleConsumptionData(moduleId: Int, beg: Int, end: Int, unit: Int) -> (avc: alertViewContent?, conso: JSON) {
		var ret: alertViewContent? = nil
		let reqRet = _network.getModuleConso(moduleId, beg: beg, end: end, unit: unit)

		if (reqRet.returnCode != D_REQUEST_SUCCESS) {
			ret = ("Couldn't retrieve consumption data", errDesc(reqRet.returnCode), "Ok")
		}
		println(reqRet.consoJSON.description) //TODO
		return (ret, reqRet.consoJSON)
	}
	
}