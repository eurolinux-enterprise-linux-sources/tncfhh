/*
 * This software is Copyright (C) 2010-2011
 * Fachhochschule Hannover (University of Applied Sciences and Arts)
 * Use is subject to license conditions.
 *
 * The main licensing options available are:
 *
 * Open Source Licensing. This is the appropriate option if you want to
 * share the source code of your application with everyone you
 * distribute it to, and you also want to give them the right to share
 * who uses it. If you wish to use TNC@FHH under Open Source Licensing,
 * you must contribute all your source code to the open source
 * community in accordance with the GPL Version 2 when your application
 * is distributed. See http://www.gnu.org/licenses/gpl-2.0.html/ or gpl-2.0.txt
 *
 * Commercial Licensing. This is the appropriate option if you are
 * creating proprietary applications and you are not prepared to
 * distribute and share the source code of your application.
 * Contact trust@f4-i.fh-hannover.de for details.
 *
 * http://trust.inform.fh-hannover.de/
 */

#ifndef ENDPOINT_DB_H
#define ENDPOINT_DB_H

#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include <tr1/unordered_map>
using std::tr1::hash;

#include <tncvpn/iel/Endpoint.h>


namespace tnc {


typedef std::tr1::unordered_map<unsigned long, Endpoint*> EP_HashMap;


/**
 * Contains a list of all endpoints. The database is realized as
 * a hashmap.
 */
class EndpointDB {
private:
	/** Hashmap containing the endpoints */
	EP_HashMap endpoints;

public:
	/**
	 * Contsructs a new endpoint_db object.
	 */
	EndpointDB();
	virtual ~EndpointDB();

	/**
	 * Adds an endpoint to the db.
	 */
	void add(Endpoint *ep);


	/**
	 * Removes an endpoint to the db.
	 */
	void remove(Endpoint *ep);


	/**
	 * Returns a hashmap of all endpoints.
	 */
	EP_HashMap* getEndpoints();


	/**
	 * Prints all endpoints on stdout.
	 */
	void printAllEndpoints() const;
};

}

#endif
