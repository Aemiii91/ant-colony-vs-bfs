import folium

def create_marker(path: list, coords: (float, float), node_id: int, color: str = 'darkred', radius: int = 5):
    popup = f"""
        <strong>ID: {node_id}</strong><br/>
        <em>{coords[0]:.6f},&nbsp;{coords[1]:.6f}</em><br/>
    """
    icon_text = ""

    if node_id in path:
        path_index = path.index(node_id)
        if path_index > 0:
            popup += f"Previous: {path[path_index-1]}<br/>"
        if path_index < len(path)-1:
            popup += f"Next: {path[path_index+1]}<br/>"
        icon_text = str(path_index+1)

    return folium.Marker(
        location=coords,
        popup=popup,
        tooltip=f"ID: {node_id}",
        icon=folium.features.DivIcon(html=f"""
            <style>
                .icon {{
                    border: 2px solid currentColor;
                    border-radius: 50%;
                    background-color: currentColor;
                    margin-top: -2px;
                    margin-left: -2px;
                    text-align: center;
                }}
                .icon:after {{
                    content: attr(data-text);
                    position: absolute;
                    display: inline-block;
                    color: white;
                    font-size: 11px;
                    z-index: 1;
                    transform: translateX(-50%);
                }}
            </style>
            <div class="icon" style="color: {color}; width: {2*radius}px; height: {2*radius}px;" data-text="{icon_text}"></div>
        """)
    )


def create_circle_marker(coords: (float, float), color: str = 'darkred', radius: int = 5):
    return folium.CircleMarker(
        location=coords,
        radius=radius,
        color=color,
        weight=2,
        threshold_scale=[0,1,2,3],
        fill_color=color,
        fill=True,
        fill_opacity=0.5
    )


def fit_locations(m: folium.Map, locations: list):
    s_w = min(locations)
    n_e = max(locations)
    m.fit_bounds([s_w, n_e])


def style_function(color):
    return lambda feature: dict(color=color, weight=3, opacity=1)


def create_legend(html: str):
    return folium.Element(f"""
        <style>
        .legend {{
            width: 280px;
            background: white;
            border: 1px solid #ddd;
            padding: 12px 16px;
            font-size: 16px;
            box-shadow: 0 2px 5px 0 rgba(0, 0, 0, 0.16), 0 2px 10px 0 rgba(0, 0, 0, 0.12);
            position: absolute;
            top: 10px;
            left: 10px;
            z-index: 10000;
        }}
        .marker-description {{
            text-align: center;
            margin-top: 4px;
        }}
        .marker-description span {{
            font-size: .85em;
            font-weight: bold;
            margin-right: 8px;
            padding-left: 12px;
            position: relative;
        }}
        .marker-description span:before {{
            content: "";
            display: inline-block;
            border: 2px solid;
            width: 8px;
            height: 8px;
            border-radius: 50%;
            position: absolute;
            left: 0;
            top: 3px;
        }}
        .marker-description span.start:before {{ border-color: #41a6b5; background-color: #41a6b57F; }}
        .marker-description span.last:before {{ border-color: #9d7cd8; background-color: #9d7cd87F; }}
        .color-palette {{
            width: 100%;
            height: 8px;
            margin: 8px 0;
        }}
        .color-palette td {{
            font-size: 0px;
            background-color: currentColor;
        }}
        .color-palette div {{
            position: relative;
        }}
        .color-palette td:not(:last-child) div:after {{
            content: "";
            position: absolute;
            height: 0;
            width: 0;
            left: 100%;
            top: -4px;
            border: 4px solid transparent;
            border-left: 4px solid currentColor;
        }}
        </style>
        <div class="legend">
            {html}
        </div>
    """)
