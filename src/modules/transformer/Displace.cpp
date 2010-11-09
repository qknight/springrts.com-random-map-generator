#include "Displace.h"
#include "ModuleFactory.h"
#include "NoiseNetwork.h"

#include "registermodule_macro.cpp"

M_REGISTER(Displace);

Displace::Displace() : DataAbstractModule(1,3,1) {
  setProperty("FIXME", 112); // FIXME setting properties should be done via makros
}

Displace::~Displace() {
}

NoiseNetwork* Displace::network() {
    // 0. query module for readieness
    //    a module is ready if all dependencies are sadisfied, if that did not happen
    //    we can't use it as libnoise could throw an exception or do other weird things...
    if (ready()) {
        //   1. create a noiseNetwork (if generator module)
        NoiseNetwork* noiseNetwork = new NoiseNetwork;

        //   2. construct the local module (in this case Perlin)
        noise::module::Displace* m_Displace = new noise::module::Displace();
        noiseNetwork->addModule(m_Displace);

        //   3. assign all properties
        //   m_Displace->SetOctaveCount (property("OctaveCount"));
        //FIXME: implement this

        //   4. connect all source modules (in case of a generator module: none) & merge the NoiseNetwork(s)
        //   foreach(input i)
        //       m_perlin->SetSourceModule(i->portnumber, i->topLevelModule);
        //       noiseNetwork->merge(i->network)
        //   foreach(input m)
        //     m_perlin->SetControlModule(m->topLevelModule);
        //     noiseNetwork->merge(m->network)

        for (int x=0; x < childCount(); ++x) {
            DataAbstractItem* chi = childItems()[x];
            if (chi->getObjectType() == DataItemType::PORT) {
                DataPort* p = static_cast<DataPort*>(chi);
                if (p->PortDirection() == PortDirection::IN || p->PortDirection() == PortDirection::MOD) {
                    // 1. reconstruct the Connection
                    DataConnection* c = static_cast<DataConnection*> (p->referenceChildItems().first());
                    // 2. reconstruct the remote port
                    DataAbstractItem* abstractPort = c->dst();
                    // 3. reconstruct the remote module
                    DataAbstractModule* module = static_cast<DataAbstractModule*> (abstractPort->parent());
                    // 4. check if it is ready
                    /*
                    if (p->PortDirection() == PortDirection::IN) {
                      NoiseNetwork* n = module->network();
                      m_Displace->SetSourceModule(p->PortNumber(), n->topLevelModule());
                      noiseNetwork += n;
                    }
                    */
                    /*
                    if (p->PortDirection() == PortDirection::MOD) {
                      NoiseNetwork* n = module->network();
                      m_Displace->SetControlModule(n->topLevelModule());
                      noiseNetwork += n;                      
                    }
                    */
                }
            }
        }

        return noiseNetwork;
    }
    return NULL;
}


