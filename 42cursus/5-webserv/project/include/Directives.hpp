/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directives.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:59:36 by kichkiro          #+#    #+#             */
/*   Updated: 2024/01/28 06:04:42 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// Libraries ------------------------------------------------------------------>

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <string>
#include <dirent.h>
#include <unistd.h>

#include "utils.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::getline;
using std::streampos;

// Classes -------------------------------------------------------------------->

class Directive {
    protected:
        typedef vector<string>::iterator VecStrIt;
        typedef vector<Directive *>::iterator VecDirIt;

        string              _type;
        bool                _is_context;
        vector<string>      _value_inline;
        vector<Directive *> _value_block;

        virtual void _parsing_inline(string raw_value);
        virtual void _parsing_block(ifstream &raw_value);

    public:
        Directive(void);
        virtual ~Directive();

        vector<string>      get_value_inline(void);
        vector<Directive *> get_value_block(void);

        static const char *_directives[];

        static void router(
            vector<Directive *> &value,
            string context,
            string directive,
            string line,
            ifstream &file
        );
};

/*!
 * @ref 
    Docs:       https://nginx.org/en/docs/ngx_core_module.html#include
    Syntax:	    include file | mask;
    Default:	———
    Context:	any
 */
class Include : public Directive {
    private:
        void _parsing(string raw_value, vector<string> &parsed_content);
        
    public:
        Include(string raw_value, vector<string> &parsed_content);
        ~Include();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#http
    Syntax:	    http { ... }
    Default:	———
    Context:	main
 */
class Http : public Directive {
    public:
        Http(string context);
        Http(ifstream &raw_value, string context);
        ~Http();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#server
    Syntax:	    server { ... }
    Default:	———
    Context:	http
 */
class Server : public Directive {
    public:
        Server(string context);
        Server(ifstream &raw_value, string context);
        ~Server();
};

// class Location : public Directive {
//     private:

//     public:

// };

// class Limit_except : public Directive {
//     private:

//     public:

// };

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#listen
    Syntax:	    listen address[:port];
    Default:	listen *:80 | *:8000;
    Context:	server
 */
class Listen : public Directive {
    public:
        Listen(string context);
        Listen(string raw_value, string context);
        ~Listen();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#root
    Syntax:	    root path;
    Default:	root html;
    Context:	http, server, location, if in location
 */
class Root : public Directive {
    public:
        Root(string context);
        Root(string raw_value, string context);
        ~Root();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#server_name
    Syntax:	    server_name name ...;
    Default:    server_name "";
    Context:	server
 */
class ServerName : public Directive {
    public:
        ServerName(string context);
        ServerName(string raw_value, string context);
        ~ServerName();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page
    Syntax:	    error_page code ... [=[response]] uri;
    Default:	———
    Context:	http, server, location, if in location
 */
class ErrorPage : public Directive {
    public:
        ErrorPage(string context);
        ErrorPage(string raw_value, string context);
        ~ErrorPage();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size
    Syntax:	    client_max_body_size size;
    Default:	client_max_body_size 1m;
    Context:	http, server, location
 */
class ClientMaxBodySize : public Directive {
    public:
        ClientMaxBodySize(string context);
        ClientMaxBodySize(string raw_value, string context);
        ~ClientMaxBodySize();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_core_module.html#alias
    Syntax:	    alias path;
    Default:	———
    Context:	location
 */
class Alias : public Directive {
    public:
        Alias(string context);
        Alias(string raw_value, string context);
        ~Alias();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_index_module.html#index
    Syntax:	    index file ...;
    Default:    index index.html;
    Context:	http, server, location
 */
class Index : public Directive {
    public:
        Index(string context);
        Index(string raw_value, string context);
        ~Index();
};

/*!
 * @ref
    Docs:       https://nginx.org/en/docs/http/ngx_http_autoindex_module.html#autoindex
    Syntax:	    autoindex on | off;
    Default:    autoindex off;
    Context:	http, server, location
 */
class Autoindex : public Directive {
    public:
        Autoindex(string context);
        Autoindex(string raw_value, string context);
        ~Autoindex();
};
