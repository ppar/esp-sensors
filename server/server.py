#
# Simple HTTP server that accepts JSON documents over POST requests
#
import http.server
import socketserver
import json

class ReqHandler(http.server.BaseHTTPRequestHandler):
    def _error(self, code, message):
        print("ERROR: " + message)
        self.send_response(code),
        self.wfile.write(bytes("ERROR: " + message + "\n", "utf-8"))
        return

    def do_POST(self):
        print('-' * 80)
        print(self.path)
        print(self.headers)

        try:
            content_length = int(self.headers['Content-Length'])
        except:
            return self._error(400,"no Content-Length")

        post_body = self.rfile.read(content_length)

        try:
            data = json.loads(post_body)
        except:
            return self._error(400,"could not parse JSON")

        print(data)

        self.send_response(200)
        self.send_header("Content-Type", "text/plain")
        self.end_headers()
        self.wfile.write(bytes("OK\n", "utf-8"))

with socketserver.TCPServer(("", 8888), ReqHandler) as httpd:
    print("Serving....")
    httpd.serve_forever()

