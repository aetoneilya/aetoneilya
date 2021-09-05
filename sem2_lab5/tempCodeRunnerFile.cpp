
            create_plane(planes, towns, line);
            break;

        case commands::PLANES_FOR_TOWN:
            planes_for_town(towns, line.at(0));
            break;

        case commands::TOWNS_FOR_PLANE:
            towns_for_plane(planes, towns, line.at(0));
            break;

        case commands::PLANES:
            planes_print(planes);
            break;

        case commands::EXIT:
            return 0;
            break;
        }
    }
    return 0;
}