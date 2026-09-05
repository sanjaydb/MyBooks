# Windows Encryption and Data-Protection Utilities in C

Ten examples built on Windows cryptography and encryption APIs.

| Program | Purpose |
| --- | --- |
| `dpapi_encrypt_file.c` | Protect a small file for the current Windows user. |
| `dpapi_decrypt_file.c` | Restore a file protected by the matching DPAPI example. |
| `dpapi_encrypt_text.c` | Protect command-line text into a binary file. |
| `dpapi_decrypt_text.c` | Recover protected text for the same Windows user. |
| `efs_encrypt_file.c` | Enable Windows EFS encryption on a file. |
| `efs_decrypt_file.c` | Remove EFS encryption from a file. |
| `base64_encode_file.c` | Convert a small file to Base64 text. |
| `base64_decode_file.c` | Decode Base64 text back into a file. |
| `sha256_file.c` | Calculate a SHA-256 file digest. |
| `secure_random.c` | Generate cryptographically secure random bytes. |

## Build

```bat
cl /W4 dpapi_encrypt_file.c /link Crypt32.lib
cl /W4 sha256_file.c /link Bcrypt.lib
cl /W4 secure_random.c /link Bcrypt.lib
```

DPAPI output can normally be decrypted only by the same Windows user account on the same computer. EFS requires an NTFS volume with EFS support; back up the EFS recovery certificate before relying on it.

Base64 is an encoding, not encryption. SHA-256 is a one-way integrity hash, not encryption. Test these educational examples with disposable files and keep independent backups of important data.

## Repository Notice

This account contains personal research, educational projects, experiments, and historical code developed over several years.

Names, domains, identifiers, and sample data appearing in older repositories may be test or demonstration values and should not, by their presence alone, be interpreted as representing an employer, customer, organization, product, or endorsement.

I periodically review older repositories for maintainability, security, documentation, and appropriate handling of confidential or proprietary information.
