//
//  ProfilesTableView.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 23/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import Foundation
import UIKit

class ProfilesTableView: UITableView, UITableViewDelegate, UITableViewDataSource {
	private var _profiles = Profiles()

	required init(coder aDecoder: NSCoder)
	{
		super.init(coder: aDecoder)
		delegate = self
		dataSource = self
	}

	// ask Profiles to update his profile list from the server
	func fetchProfiles(sender: UIViewController) {
		// if returnCode returned then display error
		if let ret = _profiles.refresh() {
			// if error, Profiles is empty and pop-up explain error
			popAlertView(sender, ("Error retreiving profiles", errDesc(ret), "Ok"))
		}
		// refresh table display
		reloadData()
	}


	/* ------------------------------------------------------------------------ */

	func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?)
	{
		if segue.identifier == "showProfileDetails" {
			if let profileDetailsVC = segue.destinationViewController as? ProfileDetailsVC {
				if let rowIndex = self.indexPathForSelectedRow()?.row { //TODO checker ca, c'est pas clean
					profileDetailsVC.setProfile(_profiles.at(rowIndex))
				}
			}
		}
	}

	// return cell count
	func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return _profiles.count()
	}

	// cell generation - called for each cell
	func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
		var cell = self.dequeueReusableCellWithIdentifier("profileCell", forIndexPath: indexPath) as! ProfileCell
		var profile = _profiles.at(indexPath.row)

		cell._profileName.text = profile.name
		return cell
	}

	// add an empty new Profile to Profiles
	func addNewProfile() -> alertViewContent? {
		let returnCode = _profiles.addNew()
		var ret: alertViewContent?

		if (returnCode == D_REQUEST_SUCCESS) {
			// refresh table display
			_profiles.refresh()
			reloadData()
		}
		else {
			// display error
			ret = ("Creating new profile failed", errDesc(returnCode), "Ok")
		}
		return ret
	}

}