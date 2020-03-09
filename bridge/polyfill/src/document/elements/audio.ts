import { Element } from '../element';
import { method } from '../UIManager';

export class AudioElement extends Element {
  constructor(tagName: string) {
    super(tagName);
  }

  play = () => {
    method(this.nodeId, 'play');
  };

  pause = () => {
    method(this.nodeId, 'pause');
  };

  fastSeek = (duration: number) => {
    method(this.nodeId, 'fastSeek', [duration]);
  };
}
