const requestify = require('requestify');
let QueryTester = {
    // override this function to make query
    MakeQuery : function() {
        return 'https://www.google.com/';
    },
    // override this function to process response
    ProcessResponse : function(responseText) {        
        console.log(responseText);
    },
    // override this function to start test
    StartTest : function() {
        console.log("Start Query Test!");

        const queryStr = this.MakeQuery();
        console.log("Test Query: " + queryStr);

        let querytester = this;
        requestify.get(queryStr)
        .then(function(response) {
            querytester.ProcessResponse(response.getBody());
        }
        );
    }
};

QueryTester.StartTest();