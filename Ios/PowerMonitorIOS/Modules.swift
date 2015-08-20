//
//  Modules.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 06/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import SwiftyJSON

// container and utilities for Modules
class Modules {
	private var _network = Network.sharedInstance
	private var _modules = [Module]()

	// return number of units inside Modules
	func count() -> Int {
		return _modules.count
	}

	// return the Module at Modules[index]
	func at(index: Int) -> Module {
		return _modules[index]
	}

	// update Modules with server Modules - ret nil if no err
	func refresh() -> Int? {
		var ret: Int!
		var res = _network.getModules()

		_modules.removeAll()
		if res.returnCode != D_REQUEST_SUCCESS {
			ret = res.returnCode
		}
		println("Modules class -> \(res.modulesJSON.description)") //dev
		append(res.modulesJSON)
		return ret
	}

	// switch module state
	func switchState(index: Int) -> Int? {
		var ret: Int!
		let returnCode = _network.turnOnOff(!_modules[index].status, id: _modules[index].id)

		if returnCode != D_REQUEST_SUCCESS && returnCode != D_STATE_ALREADY_SET {
			ret = returnCode
		}
		_modules[index].status = !(_modules[index].status)
		return ret
	}

	/* ------------------------------------------------------------------------ */

	// append 1 or + Module(s) struct(s) to Modules from JSON
	private func append(newElementJSON: JSON) {
		for (index: String, moduleJSON: JSON) in newElementJSON {
			var module = generateModuleFromJSON(moduleJSON)
			_modules.append(module)
		}
	}
}

