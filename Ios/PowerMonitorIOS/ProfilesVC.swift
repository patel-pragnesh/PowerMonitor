//
//  ProfilesVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 11/12/14.
//  Copyright (c) 2014 Alexandre Camilleri. All rights reserved.
//

import UIKit

class ProfilsVC: UIViewController {
	@IBOutlet weak var _profilesTableView: ProfilesTableView!

	override func viewWillAppear(animated: Bool) {
		_profilesTableView.fetchProfiles(self)
	}

	override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
		_profilesTableView.prepareForSegue(segue, sender: sender)
	}

	/* ------------------------------------------------------------------------ */

	@IBAction func addNewProfilTapped(sender: UIButton) {
		let ret: alertViewContent? = _profilesTableView.addNewProfile()

		if (ret != nil) {
			popAlertView(self, ret!)
		}
	}
}
