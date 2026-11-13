# Windows-Keyboard-Mouse-Filter JavaScript / TypeScript SDK

`npm install windows-keyboard-mouse-filter`

Node.js 20+ Windows x64. Bundled Node-API v8 addon and product native DLL; no compiler or Python required to install. Driver installation and original product licensing remain separate. Supported families: keyboard, mouse.

```js
const { Interceptor } = require("windows-keyboard-mouse-filter");
const client = new Interceptor();
try { console.log(client.info()); } finally { client.close(); }
```

[API documentation](docs/API.md). Construction does not start capture.
