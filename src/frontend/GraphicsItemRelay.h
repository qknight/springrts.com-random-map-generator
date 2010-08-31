#ifndef GRAPHICSiTEMRELAY_H
#define GRAPHICSiTEMRELAY_H

#include <QPointF>
#include <QObject>

class Port;
class Connection;

/*! relays function calls between a port and a connection 
    this prevents that a Port has direct access to a Connection (with a pointer) and
    vice versa. the primary concept is to make pointer management easier and less
    error phrone.*/
class GraphicsItemRelay : public QObject {
    Q_OBJECT
    friend class Port;
    friend class Connection;
    friend class GraphcisItemRelayInterface;
    
protected:
    GraphicsItemRelay(Port* p, Connection* c);
     ~GraphicsItemRelay();
    /*! this function is called when one of the client objects is destroyed */
    void updatePosition(QPointF pos);
    QPointF pos();
private:
    Connection* m_connection;
    Port* m_port;
    QPointF m_pos;
};

#endif
