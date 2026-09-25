# 01: Inventory Advantech SDK and hardware manual provenance

Status: ready-for-human
Blocked by: None

## Outcome

Create a reviewable inventory of bundled Advantech and other third-party material, its source, and its stated license or redistribution terms. Avoid asserting that the project owner holds copyright in this material.

## Work

1. Inventory `references/advantech_sdk/` by meaningful source/package and file type, including nested third-party components, generated files, binaries, and any license or copyright notices. Include `docs/hardware/PCI-1716_Series_User_Manual_Ed.2_FINAL.pdf`.
2. Trace each identified package or document to primary evidence: headers, bundled licenses, publisher documentation, official download pages, or official terms. Cite exact local paths and authoritative URLs. Separate confirmed facts from inference and unresolved questions.
3. State the scope of each permission claim precisely. Do not assume an example source license covers an SDK binary, generated artifact, manual, or nested component.
4. Check how project documentation refers to these assets. Add a concise project-facing document under `docs/` with an inventory table, attribution/notice instructions, unresolved redistribution questions, and the boundary for any future project-owner copyright notice. Link it from the README or a suitable documentation index.
5. Do not remove assets, rewrite Git history, publish changes, or change runtime/deployment files.

## Deliverables and acceptance

- A source-backed Markdown document exists under `docs/` and lists each materially distinct bundled source or document, file scope, origin, rights statement, evidence, and action or uncertainty.
- Local copyright and license notices remain intact; no unsupported claim of redistribution permission is made.
- The README links to the document, and the ticket records findings and checks under `## Comments`.

## Comments

- Inventory and documentation work is complete. Remaining decision for the repository owner: locate written Advantech redistribution permission, or replace the public manual copy with its official link and decide how to handle unresolved SDK bundle files.
- Added [`docs/third-party-provenance.md`](../../../docs/third-party-provenance.md) with a grouped inventory of the 1,667-file Advantech examples bundle, its file-level notices, the nested `enum34` and Eclipse helper notices, and the PCI-1716 manual. Linked the inventory from the README repository map.
- Local checks: `find references/advantech_sdk/DAQ_examples -type f | wc -l` reported 1,667; there are 206 `.o` files and 28 Qt release executables. A scan found 141 files carrying Advantech's MIT-style permission wording and ten copyright-bearing files without that wording, including older counter examples. The `enum34/LICENSE` has BSD-style redistribution conditions. The Java helper's header identifies EPL 1.0.
- `pdftotext` of printed manual page ii confirms ©2025 Advantech, all rights reserved, and prior written permission required for reproduction/copying/transmission. Advantech's manual support page lists the Edition 2 title and 2025-06-13 date: https://www.advantech.com/en-us/support/details/manual?id=1-7O1XO . Its official PDF is https://advdownload.advantech.com/productfile/Downloadfile1/1-33HO84K/PCI-1716_Series_User_Manual_Ed.2_FINAL.pdf . Advantech DAQNavi driver information is at https://www.advantech.com/emt/support/details/driver?id=1-LXHFQJ . These publisher pages establish source/package identity; no blanket redistribution terms for the full example bundle were found.
- Redistribution of the full SDK examples bundle and the existing manual copy remains unresolved. The inventory explicitly distinguishes file-level source grants from generated content, assets, binaries, and manual rights; it does not claim project ownership of vendor material.
- Verification: reviewed exact embedded notices, scanned extension/build artifact counts, extracted manual page ii, and checked the README link target. No tests run; documentation only.
