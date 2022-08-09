/*
* Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/

import './dom';
// import './query-selector';
import {console} from './console';
import {fetch, Headers, Request, Response} from './fetch';
import {matchMedia} from './match-media';
import {location} from './location';
import {history} from './history';
import {navigator} from './navigator';
import {XMLHttpRequest} from './xhr';
import {asyncStorage} from './async-storage';
import {URLSearchParams} from './url-search-params';
import {URL} from './url';
import {webf} from './webf';

defineGlobalProperty('console', console);
defineGlobalProperty('Request', Request);
defineGlobalProperty('Response', Response);
defineGlobalProperty('Headers', Headers);
defineGlobalProperty('fetch', fetch);
defineGlobalProperty('matchMedia', matchMedia);
defineGlobalProperty('location', location);
defineGlobalProperty('history', history);
defineGlobalProperty('navigator', navigator);
defineGlobalProperty('XMLHttpRequest', XMLHttpRequest);
defineGlobalProperty('asyncStorage', asyncStorage);
defineGlobalProperty('URLSearchParams', URLSearchParams);
defineGlobalProperty('URL', URL);
defineGlobalProperty('webf', webf);

function defineGlobalProperty(key: string, value: any, isEnumerable: boolean = true) {
    Object.defineProperty(globalThis, key, {
        value: value,
        enumerable: isEnumerable,
        writable: true,
        configurable: true
    });
}
