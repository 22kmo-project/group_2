#ifndef RESTAPIURL_H
#define RESTAPIURL_H

#include <QString>

class restApiURL
{
public:
    restApiURL();
    static QString getBaseUrl();
private:
    static QString base_url;
};

#endif // RESTAPIURL_H
