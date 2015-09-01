//
//  ModulesVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 21/11/14.
//  Copyright (c) 2014 Alexandre Camilleri. All rights reserved.
//

// View controller for Modules view
// It's also the main view controller

import UIKit

class ModulesVC: UIViewController {
	@IBOutlet weak var _useraccountLabel: UILabel!
	@IBOutlet weak var _modulesTableView: ModulesTableView!

	override func viewWillAppear(animated: Bool) {
		let prefs = NSUserDefaults.standardUserDefaults()

		if !isUserLogged() {
			//Goto login view for log-in
			self.performSegueWithIdentifier("gotoLogin", sender: self)
		}
		else {
			_modulesTableView.fetchModules(self)
			_useraccountLabel.text = prefs.valueForKey("USERACCOUNT") as! String?
		}
	}

	override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
		_modulesTableView.prepareForSegue(segue, sender: sender)
	}

	@IBAction func logoutTapped() {
		let appDomain = NSBundle.mainBundle().bundleIdentifier

		// clean of userEnv
		NSUserDefaults.standardUserDefaults().removePersistentDomainForName(appDomain!)
		// send back to Login view
		self.performSegueWithIdentifier("gotoLogin", sender: self)
	}
}
