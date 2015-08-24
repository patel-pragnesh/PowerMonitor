//
//  ProfileDetailsVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 12/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

class ProfileDetailsVC: UIViewController, UITextFieldDelegate
{
	@IBOutlet weak var _nameTextField: UITextField!
	@IBOutlet weak var _pollingTextField: UITextField!
	@IBOutlet weak var _pollingStepper: UIStepper!
	private var _profile: Profile!
	private var _profileDetails = ProfileDetails()

	override func viewWillAppear(animated: Bool) {
		_nameTextField.delegate = self
		_pollingTextField.delegate = self
		_nameTextField.text = _profile.name
		_pollingTextField.text = _profile.polling.description
		self.navigationItem.title = _profile.name
	}

	override func viewWillDisappear(animated: Bool) {
		let ret: alertViewContent? = _profileDetails.updatePolling(_profile.id, polling: _pollingTextField.text.toInt()!)

		if (ret != nil) {
			popAlertView(self, ret!)
		}
	}

	override func viewDidAppear(animated: Bool) {
		_pollingStepper.wraps = true
		_pollingStepper.autorepeat = true
		_pollingStepper.minimumValue = Double(D_POLLING_MIN_VAL)
		_pollingStepper.maximumValue = Double(D_POLLING_MAX_VAL)
		_pollingStepper.stepValue = Double(D_POLLING_STEP_VAL)
		_pollingStepper.value = Double(_profile.polling)

	}

	@IBAction func pollingValueChanged(sender: UIStepper) {
		_pollingTextField.text = Int(sender.value).description
	}

	@IBAction func deleteProfileTapped() {
		
		let ret: alertViewContent? = _profileDetails.deleteProfile(_profile.id)

		if (ret != nil) {
			popAlertView(self, ret!)
		}
		else {
			self.navigationController?.popViewControllerAnimated(true)
		}
	}

	func textFieldShouldReturn(textField: UITextField) -> Bool {
		self.view.endEditing(true)

		if let ret = _profileDetails.editName(_profile!.id , newName: _nameTextField.text) {
			popAlertView(self, ret)
		}
		return false
	}

	override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?)
	{
		if segue.identifier == "showProfileSchedule" {
			if let profileTimeSlotsVC = segue.destinationViewController as? ProfileTimeSlotsVC {
				profileTimeSlotsVC.profile = _profile
			}
		}
	}

	/* ------------------------------------------------------------------------ */

	func setProfile(profile: Profile) {
		_profile = profile
	}
}