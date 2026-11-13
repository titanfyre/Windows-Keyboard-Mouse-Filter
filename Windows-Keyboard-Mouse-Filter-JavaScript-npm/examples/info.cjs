const {Interceptor}=require("windows-keyboard-mouse-filter");const io=new Interceptor();try{console.log(io.info())}finally{io.close()}
