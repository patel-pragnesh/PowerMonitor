//
//  LoginVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 21/11/14.
//  Copyright (c) 2014 Alexandre Camilleri. All rights reserved.
//

import UIKit

class LoginVC: UIViewController {
	@IBOutlet weak var _txtMail: UITextField!
	@IBOutlet weak var _txtPassword: UITextField!
	private var _login = Login()

	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view.
		_login.connect()

		//TOCLEAN dev purpose
		_txtMail?.text = "alexandre.camilleri@epitech.eu"
		_txtPassword?.text = "alexandre"
	}

	@IBAction func signinTapped() {
		var mail = String(_txtMail.text)
		var pwd = String(_txtPassword.text)

		if let res = _login.authentification(mail, pwd: pwd) {
			popAlertView(self, res)
		}
		else {
			var uEnv = NSUserDefaults.standardUserDefaults()
			// update prefs
			uEnv.setObject(mail, forKey: "USERACCOUNT")
			uEnv.setInteger(1, forKey: "ISLOGGEDIN")
			uEnv.synchronize()
			// dismiss view and present ModuleView
			self.dismissViewControllerAnimated(true, completion: nil)
		}
	}

}
