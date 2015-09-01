//
//  ModuleDetailsVC.swift
//  PowerMonitorIOS
//
//  Created by Alexandre Camilleri on 09/03/15.
//  Copyright (c) 2015 Alexandre Camilleri. All rights reserved.
//

import UIKit
import SwiftCharts

class ModuleDetailsVC: UIViewController, UITextFieldDelegate  {
	@IBOutlet weak var _nameTextField: UITextField!
	@IBOutlet weak var _serialNumberLabel: UILabel!
	@IBOutlet weak var _defaultProfileLabel: UILabel!
	@IBOutlet weak var _internalProfileLabel: UILabel!
	private var _module: Module!
	private var _moduleDetails = ModuleDetails()

	override func viewWillAppear(animated: Bool) {
		_nameTextField.delegate = self
		_nameTextField.text = _module.name
		_serialNumberLabel.text = _module.serial.description
		_defaultProfileLabel.text = _module.defaultProfileName
		self.navigationItem.title = _module.name
	}

	func textFieldShouldReturn(textField: UITextField) -> Bool {
		self.view.endEditing(true)

		if let ret = _moduleDetails.editName(_module.id , newName: _nameTextField.text) {
			popAlertView(self, ret)
		}
		return false
	}

	override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
		if let chartVC = segue.destinationViewController as? ChartVC {
			chartVC.setModuleId(_module.id)
		}
	}

	/* ------------------------------------------------------------------------ */

	func setModule(module: Module) {
		_module = module
	}
}
