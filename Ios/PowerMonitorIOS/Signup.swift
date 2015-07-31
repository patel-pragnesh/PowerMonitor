//
//  Signup.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 23/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

class Signup {
	private var _network = Network.sharedInstance

	func signUp(mail: String, pwd: String, confirmPwd: String) -> alertViewContent? {
		var ret: alertViewContent? = nil

		if (mail.isEmpty || pwd.isEmpty || confirmPwd.isEmpty) {
			ret = ("Sign Up Failed!", "Please enter an Email and a Password", "Ok")
		}
		else if pwd != confirmPwd {
			ret = ("Sign Up Failed!", "Passwords doesn't Match", "Ok")
		}
		return ret
	}

}