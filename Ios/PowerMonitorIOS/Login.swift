//
//  Login.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 23/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

// VPS ovh
let D_SERVER_IP: String					= "62.4.24.188"
let D_SERVER_PORT: Int					= 4242

class Login {
	private var _network = Network.sharedInstance

	// connect to server - asynchronous
	func connect() {
			_network.connect(D_SERVER_IP, port: D_SERVER_PORT)
	}

	// user authentification
	func authentification(mail: String, pwd: String) -> alertViewContent? {
		var ret: alertViewContent? = nil

		if (mail.isEmpty || pwd.isEmpty) {
			ret = ("Sign in Failed!", "Please fill Mail and Password fields", "Ok")
		}
		if let res: Int? = _network.login(mail, password: pwd) {
			if res == nil {
				// retry connecting to server
				connect()
				ret = ("Can't connect to the server", "Retry later or contact support", "Ok")
			}
			else if res != D_REQUEST_SUCCESS {
				ret = ("Sign in Failed!", errDesc(res!), "Ok")
			}
		}
		return ret
	}

}