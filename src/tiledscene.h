/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2017 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _TILEDSCENE_H_
#define _TILEDSCENE_H_

#include "game.h"
#include "scene.h"
#include "tmxmap.h"
#include "tmxtileset.h"
#include "tmxtilelayer.h"

#include <QSGTexture>
#include <QQuickWindow>
#include <QSGSimpleMaterialShader>
#include <QSGGeometryNode>
#include "tiledlayer.h"

class TiledScene : public Scene
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QQmlListProperty<TiledLayer> layers READ layers)
public:
    TiledScene(Game *parent = 0);

    QUrl source() const;
    void setSource(const QUrl &source);

    QQuickItem *background() const;
    void setBackground(QQuickItem *);

    QQmlListProperty<TiledLayer> layers();

    static void append_layer(QQmlListProperty<TiledLayer> *list, TiledLayer *layer);
    static int count_layer(QQmlListProperty<TiledLayer> *list);
    static TiledLayer *at_layer(QQmlListProperty<TiledLayer> *list, int index);

    TMXMap *tiledMap() const { return m_map; }
    virtual void componentComplete();
signals:
    void sourceChanged();
    void backgroundChanged();
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
private:
    TMXMap *m_map;
    QUrl m_source;
    QQuickItem *m_background;
    QPixmap m_image;
    QList<TiledLayer *> m_layers;

    bool loadMap(const QString &source);
    void loadBackground();
    void loadLayers();
    void loadTileLayer(const TMXTileLayer &layer);
    void loadImageLayer(const TMXImageLayer &layer);
    // NOTE: Object layers are loaded by the TiledLayer and TiledObject classes.
};


#endif // _TILEDSCENE_H_

