/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Ken Zangelin
*/
#include "logMsg/logMsg.h"

#include "serviceRoutines/getNgsi10ContextEntityTypesAttribute.h"
#include "serviceRoutines/badVerbGetOnly.h"
#include "serviceRoutines/badRequest.h"
#include "rest/RestService.h"

#include "unittest.h"



/* ****************************************************************************
*
* rs - 
*/
static RestService rs[] = 
{
  { "GET", Ngsi10ContextEntityTypesAttribute, 5, { "ngsi10", "contextEntityTypes", "*", "attributes", "*" }, "", getNgsi10ContextEntityTypesAttribute },
  { "*",   Ngsi10ContextEntityTypesAttribute, 5, { "ngsi10", "contextEntityTypes", "*", "attributes", "*" }, "", badVerbGetOnly                       },
  { "*",   InvalidRequest,                    0, { "*", "*", "*", "*", "*", "*"                           }, "", badRequest                           },
  { "",    InvalidRequest,                    0, {                                                        }, "", NULL                                 }
};



/* ****************************************************************************
*
* notFound - 
*/
TEST(getNgsi10ContextEntityTypesAttribute, notFound)
{
  ConnectionInfo ci("/ngsi10/contextEntityTypes/entity11/attributes/Attribute11",  "GET", "1.1");
  const char*    outfile = "ngsi10.queryContextResponse.getNgsi10ContextEntityTypesAttribute.valid.xml";
  std::string    out;

  utInit();

  ci.outFormat = XML;
  out          = restService(&ci, rs);
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile)) << "Error getting test data from '" << outfile << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}