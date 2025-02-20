#ifndef PORTALCONFIGRESPONSE_H
#define PORTALCONFIGRESPONSE_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QXmlStreamReader>

#include "gpgateway.h"

class PortalConfigResponse
{
public:
    PortalConfigResponse();
    ~PortalConfigResponse();

    static PortalConfigResponse parse(const QByteArray xml);

    const QByteArray rawResponse() const;
    const QString &username() const;
    QString password() const;
    QString userAuthCookie() const;
    QString prelogonUserAuthCookie() const;
    QList<GPGateway> allGateways() const;
    void setAllGateways(QList<GPGateway> gateways);

    void setUsername(const QString username);
    void setPassword(const QString password);

private:
    static QString xmlUserAuthCookie;
    static QString xmlPrelogonUserAuthCookie;
    static QString xmlGateways;

    QByteArray m_rawResponse;
    QString m_username;
    QString m_password;
    QString m_userAuthCookie;
    QString m_prelogonAuthCookie;

    QList<GPGateway> m_gateways;

    void setRawResponse(const QByteArray response);
    void setUserAuthCookie(const QString cookie);
    void setPrelogonUserAuthCookie(const QString cookie);

    static QList<GPGateway> parseGateways(QXmlStreamReader &xmlReader);
    static QMap<QString, int> parsePriorityRules(QXmlStreamReader &xmlReader);
    static QString parseGatewayName(QXmlStreamReader &xmlReader);
};

#endif // PORTALCONFIGRESPONSE_H
