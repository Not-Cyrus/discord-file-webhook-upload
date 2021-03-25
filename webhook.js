const readline = require("readline")
const request = require("request")
const fs = require("fs")

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})

rl.question("Input the webhook URL: ",function(webhookURL){
    rl.question("Input the file path: ",function(filePath){
        var req = request.post(webhookURL,function(err,resp,body){
            if (err) {
                console.error(err)
            }
        })
        var form = req.form();
        form.append("file",fs.createReadStream(filePath))
    })
})
