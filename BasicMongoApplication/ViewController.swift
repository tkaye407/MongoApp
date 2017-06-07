//
//  ViewController.swift
//  BasicMongoApplication
//
//  Created by Tyler KAye on 6/2/17.
//  Copyright © 2017 MongoDB. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var label: UILabel!
    @IBOutlet weak var textField: UITextField!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


    @IBAction func sendToMemory(_ sender: Any) {
        label.text = textField.text
        textField.text = ""
    }

    @IBAction func bringFromMemory(_ sender: Any) {
        label.text = textField.text
        textField.text = ""
    }
}

