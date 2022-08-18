#!/bin/bash

# listen on 443 using ssl keys (ssl test)
openssl s_server -key key.pem -cert cert.pem -accept 443
