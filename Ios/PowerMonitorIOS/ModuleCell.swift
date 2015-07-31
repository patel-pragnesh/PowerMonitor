//
//  ModuleCell.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 07/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit

class ModuleCell: UITableViewCell
{
	var _moduleId: Int!
	var _indexPath: NSIndexPath!
	@IBOutlet weak var _moduleName: UILabel!
	@IBOutlet weak var _moduleSwitch: UISwitch!
}