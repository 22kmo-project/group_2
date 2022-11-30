#include "restapiurl.h"

restApiURL::restApiURL()
{

}

QString restApiURL::getBaseUrl()
{
    return base_url;
}


QString restApiURL::base_url{
    "http://localhost:3000"
};
