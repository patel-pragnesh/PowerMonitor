//
//  ProfileTimeSlotsVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 09/06/2015.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

let DIR_PREVIOUS = -1
let DIR_NEXT = 1

class ProfileTimeSlotsVC: UIViewController {
	var profile: Profile!
	@IBOutlet weak var timeSlotsTableView: TimeSlotsTableView!

	override func viewDidLoad() {
		timeSlotsTableView.setProfile(profile)
		updateDisplay()
	}

	@IBAction func addNewTapped(sender: AnyObject) {
		timeSlotsTableView.addNewTimeSlot()
		updateDisplay()
	}

	@IBAction func previousTapped(sender: AnyObject) {
		timeSlotsTableView.changeDay(DIR_PREVIOUS)
		updateDisplay()
	}

	@IBAction func nextTapped(sender: AnyObject) {
		timeSlotsTableView.changeDay(DIR_NEXT)
		updateDisplay()
	}

	override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
		timeSlotsTableView.prepareForSegue(segue, sender: sender)
	}

	func updateDisplay() {
		timeSlotsTableView.render()
		self.navigationItem.title = getDay(timeSlotsTableView.day)
	}
}