from http.server import HTTPServer, SimpleHTTPRequestHandler

class CustomHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        # Add COEP and COOP headers
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        super().end_headers()

# Define the server address and port
server_address = ("", 8000)  # Serves on localhost:8000
httpd = HTTPServer(server_address, CustomHandler)

print("Serving on port 8000...")
httpd.serve_forever()