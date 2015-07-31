//
//  ModulesTableVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 21/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

class ModulesTableView: UITableView, UITableViewDelegate, UITableViewDataSource
{
	private var _modules = Modules()

	required init(coder aDecoder: NSCoder)
	{
		super.init(coder: aDecoder)
		delegate = self
		dataSource = self
	}

	// ask Modules to update his module list from the server
	func fetchModules(sender: UIViewController) {
		// if returnCode returned then display error
		if let ret = _modules.refresh() {
			// if error, Modules is empty and pop-up explain error
			popAlertView(sender, ("Error retreiving modules", errDesc(ret), "Ok"))
		}
		// refresh table display
		reloadData()
	}

	func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?)
	{
		if segue.identifier == "showModuleDetails" {
			if let moduleDetailsVC = segue.destinationViewController as? ModuleDetailsVC {
				if let rowIndex = self.indexPathForSelectedRow()?.row { //TODO checker ca, c'est pas clean
					moduleDetailsVC.setModule(_modules.at(rowIndex))
				}
			}
		}
	}

	@IBAction func moduleStateSwitched(sender: UISwitch) {
		var buttonPos = sender.convertPoint(CGPointZero, toView: self)
		var index = indexPathForRowAtPoint(buttonPos)?.item

		if let ret = _modules.switchState(index!) {
			popAlertView(self, ("Error turning On/Off", errDesc(ret), "Ok"))
		}
	}

	/* -- */

	// return total number of cells
	internal func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int
	{
		return _modules.count()
	}

	// cell content generation - called for each cell
	internal func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell
	{
		var cell = dequeueReusableCellWithIdentifier("moduleCell", forIndexPath: indexPath) as! ModuleCell
		var module = _modules.at(indexPath.row)

		cell._indexPath = indexPath
		cell._moduleId = module.id
		cell._moduleName.text = module.name
		cell._moduleSwitch.setOn(module.status, animated: false)
		return cell
	}
}
