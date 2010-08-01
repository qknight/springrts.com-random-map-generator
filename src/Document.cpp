/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Document.h"
#include "Model.h"
#include "GraphicsScene.h"
#include "ItemView.h"

Document::Document() {
    model = new Model;
    scene = new GraphicsScene(model);
    itemView = new ItemView(scene, model);

    scene->setLoadableModuleNames(model->LoadableModuleNames());
    connect(scene, SIGNAL(CreateModuleSignal(QString,QPoint)),
            this, SLOT(CreateModuleSlot(QString,QPoint)));

    model->insertModule("NoiseGen::Billow", QPoint(-200,0));
    model->insertModule("NoiseGen::Perlin", QPoint(-200,200));
    model->insertModule("NoiseGen::Perlin", QPoint( 0,350));
    model->insertModule("Utils::NoiseMap" , QPoint( 350,50));
    model->insertModule("Selector::Selector", QPoint(100,100));
    
//     QModelIndex port1, port2;
//     model->insertConnection(port1, port2);

//   scene->addLine(-500,-500,-500,-501);
//   scene->addLine(500,500,500,501);
//   scene->addLine(-100,0,100,0);
//   scene->addLine(0,-100,0,100);
}

Document::~Document() {
    delete itemView;
    delete scene;
    delete model;
}

void Document::CreateModuleSlot(QString type, QPoint position) {
    model->insertModule(type, position);
}
