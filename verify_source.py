"""Validate source/resource integrity before making local changes."""
from pathlib import Path
import hashlib,json,sys
ROOT=Path(__file__).resolve().parent
def main():
    manifest=json.loads((ROOT/'SOURCE_MANIFEST.json').read_text('utf-8'))
    failures=[]
    for entry in manifest['files']:
        path=(ROOT/entry['path']).resolve()
        if not path.is_relative_to(ROOT) or not path.is_file():failures.append(entry['path']+': missing/invalid');continue
        digest=hashlib.sha256()
        with path.open('rb') as f:
            for chunk in iter(lambda:f.read(1024*1024),b''):digest.update(chunk)
        if digest.hexdigest()!=entry['sha256']:failures.append(entry['path']+': changed')
    print(json.dumps({'ok':not failures,'checked':len(manifest['files']),'failures':failures},ensure_ascii=False,indent=2))
    return int(bool(failures))
if __name__=='__main__':raise SystemExit(main())
