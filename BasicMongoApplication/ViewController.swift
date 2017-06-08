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
    
    var db: OpaquePointer!
    var client: OpaquePointer!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Create connections to db and client
        db = libmongodbcapi_db_new(0, nil, nil)
        client = libmongodbcapi_db_client_new(db)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // Destroy connections to db and client
    override func viewWillDisappear(_ animated: Bool) {
        libmongodbcapi_db_client_destroy(client)
        libmongodbcapi_db_destroy(db)
    }

    func communicate(input: String) -> String {
        let i: [CChar]? = input.cString(using: String.Encoding.utf8)
        
        let out = UnsafeMutablePointer<UnsafeMutableRawPointer?>.allocate(capacity: 1)
        let o: [CChar]? = String(repeating: "5", count: 512).cString(using: String.Encoding.utf8)
        out.initialize(to: unsafeBitCast(o, to: UnsafeMutableRawPointer.self))
        let outSize = UnsafeMutablePointer<Int>.allocate(capacity: 8)
        
//        libmongodbcapi_db_client_wire_protocol_rpc(OpaquePointer!, UnsafeRawPointer!, Int, UnsafeMutablePointer<UnsafeMutableRawPointer?>!, UnsafeMutablePointer<Int>!)
        
        let err = libmongodbcapi_db_client_wire_protocol_rpc(client, i, input.lengthOfBytes(using: String.Encoding.utf8), out, outSize)
        print(err)
        if err != 0 {
            out.deallocate(capacity: 512)
            outSize.deallocate(capacity: 32)
            return "ERROR"
        }
        
//        let str = o.flatMap { $0 as? String }.joined()
        let str = o?.reduce("", {$0 + String(UnicodeScalar(UInt8($1)))})
//        return str
        return str!
//        String(data: o, encoding: .utf8)
    }
    
    
    @IBAction func sendToMemory(_ sender: Any) {
        // call wire protocol
        print("Calling C\n")
        let s = communicate(input: "Test String!")
        print(s)
        
        label.text = textField.text
        textField.text = ""
    }

    @IBAction func bringFromMemory(_ sender: Any) {
        let num = generateNum()
        label.text = textField.text
        textField.text = "\(num)"
    }
}

