//
//  signupVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 21/11/14.
//  Copyright (c) 2014 Alexandre Camilleri. All rights reserved.
//

import UIKit

class signupVC: UIViewController {
	@IBOutlet weak var _txtEmail: UITextField!
	@IBOutlet weak var _txtPassword: UITextField!
	@IBOutlet weak var _txtConfirmPassword: UITextField!
	private var _signup = Signup()

	@IBAction func signupTapped() {
		var mail = String(_txtEmail.text)
		var pwd = String(_txtPassword.text)
		var confirmPwd = String(_txtConfirmPassword.text)

		if let res = _signup.signUp(mail, pwd: pwd, confirmPwd: confirmPwd) {
				popAlertView(self, res)
		}
		else {
			self.dismissViewControllerAnimated(true, completion: nil)
		}
	}

	@IBAction func gotoBackToLogin() {
		self.dismissViewControllerAnimated(true, completion: nil)
	}
	
}
