#include <iostream>
#include <wx/curl/base.h>
#include <wx/curl/http.h>


int main()
  {
  wxCurlHTTP m_connection;
  m_connection.Init();
  m_connection.SetVerbose(true);
  m_connection.SetOpt(CURLOPT_TIMEOUT, 30);
#ifdef NO_VERIFY
  m_connection.SetOpt( CURLOPT_SSL_VERIFYPEER, 0L);
  m_connection.SetOpt( CURLOPT_SSL_VERIFYHOST, 0L);
#else
  if (!m_connection.SetCAInfo("./cacert.pem", wxEmptyString))
    printf("Can't find cacert.pem\n");
#endif
  m_connection.SetFullURL("https://github.com/airbagi");
  //
  char *buf = NULL;
  //
  if (m_connection.Get(buf)>0)
    {
    // string strResult = buf;
    printf("Result = %s\n", buf);
    delete []buf;
    }
  else
    {
    printf("Fault %s! \n", (const char*) m_connection.GetErrorString().mb_str());
    }
  // finish
  return 0;
  }
